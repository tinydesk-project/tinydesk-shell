#include "tdsh.h"

#include <errno.h>
#include <limits.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDSH_ALLOC_MAGIC 0x5553484Cu /* USHL */

typedef union
{
    struct
    {
        size_t size;
        uint32_t magic;
    } meta;
    max_align_t alignment;
} tdsh_alloc_header_t;

typedef struct
{
    tdsh_core_config_t cfg;
    char hostname[TDSH_HOSTNAME_MAX];
    char default_user[TDSH_USERNAME_MAX];
    char fs_root[TDSH_MAX_REAL_PATH];
    tdsh_command_t commands[TDSH_MAX_COMMANDS];
    size_t command_count;
    bool initialized;
} tdsh_core_state_t;

static tdsh_core_state_t s_core;
bool tdsh_session_valid(const tdsh_session_t *session)
{
    if(!session||!session->username[0])return false;
    if(!s_core.cfg.user_generation)return true;
    uint32_t current=s_core.cfg.user_generation(session->username);
    return current&&current==session->user_generation;
}

tdsh_role_t tdsh_session_role(const tdsh_session_t *session)
{
    if(!tdsh_session_valid(session))return TDSH_ROLE_USER;
    if(!strcmp(session->username,"root"))return TDSH_ROLE_ROOT;
    tdsh_role_t role=s_core.cfg.user_role?s_core.cfg.user_role(session->username):TDSH_ROLE_USER;
    return role==TDSH_ROLE_ADMIN?role:TDSH_ROLE_USER;
}
uint32_t tdsh_session_rights(const tdsh_session_t *session)
{
    tdsh_role_t role=tdsh_session_role(session);
    if(role==TDSH_ROLE_ROOT)return TDSH_RIGHT_ALL;
    if(!tdsh_session_valid(session))return 0;
    return s_core.cfg.user_rights?(s_core.cfg.user_rights(session->username)&TDSH_RIGHT_ALL):role==TDSH_ROLE_ADMIN?TDSH_RIGHTS_ADMIN:TDSH_RIGHTS_USER;
}
bool tdsh_session_has_right(const tdsh_session_t *session,uint32_t right)
{
    return (tdsh_session_rights(session)&right)==right;
}
static atomic_size_t s_live_blocks;
static atomic_size_t s_live_bytes;
static atomic_size_t s_peak_blocks;
static atomic_size_t s_peak_bytes;
static atomic_size_t s_total_allocations;
static atomic_size_t s_failed_allocations;

static void atomic_peak(atomic_size_t *peak, size_t value)
{
    size_t seen = atomic_load_explicit(peak, memory_order_relaxed);
    while (value > seen &&
           !atomic_compare_exchange_weak_explicit(peak, &seen, value,
                                                  memory_order_relaxed,
                                                  memory_order_relaxed))
    {
    }
}

static void *raw_malloc(size_t n)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (p && p->malloc_fn)
        return p->malloc_fn(p->context, n);
    return malloc(n);
}

static void *raw_realloc(void *ptr, size_t n)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (p && p->realloc_fn)
        return p->realloc_fn(p->context, ptr, n);
    return realloc(ptr, n);
}

static void raw_free(void *ptr)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (p && p->free_fn)
    {
        p->free_fn(p->context, ptr);
        return;
    }
    free(ptr);
}

int tdsh_core_init(const tdsh_core_config_t *config)
{
    if (!config || !config->hostname || !config->default_user || !config->fs_root)
    {
        return -EINVAL;
    }
    if (strlen(config->hostname) >= sizeof(s_core.hostname) ||
        strlen(config->default_user) >= sizeof(s_core.default_user) ||
        strlen(config->fs_root) >= sizeof(s_core.fs_root))
    {
        return -ENAMETOOLONG;
    }

    memset(&s_core, 0, sizeof(s_core));
    snprintf(s_core.hostname, sizeof(s_core.hostname), "%s", config->hostname);
    snprintf(s_core.default_user, sizeof(s_core.default_user), "%s", config->default_user);
    snprintf(s_core.fs_root, sizeof(s_core.fs_root), "%s", config->fs_root);

    s_core.cfg = *config;
    s_core.cfg.hostname = s_core.hostname;
    s_core.cfg.default_user = s_core.default_user;
    s_core.cfg.fs_root = s_core.fs_root;
    if (s_core.cfg.history_length == 0)
        s_core.cfg.history_length = 50;
    s_core.initialized = true;
    return 0;
}

void tdsh_core_reset(void)
{
    /* This function is for tests/startup reconfiguration only. It intentionally
     * does not free caller-owned command descriptors or active sessions. */
    memset(&s_core, 0, sizeof(s_core));
}

const tdsh_core_config_t *tdsh_core_config(void)
{
    return s_core.initialized ? &s_core.cfg : NULL;
}

const char *tdsh_platform_name(void)
{
    if (s_core.cfg.platform && s_core.cfg.platform->name)
    {
        return s_core.cfg.platform->name;
    }
    return "generic-c";
}

int tdsh_session_init(tdsh_session_t *session,
                      const char *username,
                      bool interactive)
{
    if (!s_core.initialized || !session)
        return -EINVAL;
    if (!username || !username[0])
        username = s_core.cfg.default_user;
    if (strlen(username) >= TDSH_USERNAME_MAX)
        return -ENAMETOOLONG;

    memset(session, 0, sizeof(*session));
    snprintf(session->username, sizeof(session->username), "%s", username);
    session->user_generation=s_core.cfg.user_generation?s_core.cfg.user_generation(username):0;
    snprintf(session->hostname, sizeof(session->hostname), "%s", s_core.cfg.hostname);
    if (strcmp(username, "root") == 0)
    {
        snprintf(session->home, sizeof(session->home), "/root");
    }
    else
    {
        int n = snprintf(session->home, sizeof(session->home), "/home/%s", username);
        if (n < 0 || (size_t)n >= sizeof(session->home))
            return -ENAMETOOLONG;
    }
    snprintf(session->cwd, sizeof(session->cwd), "%s", session->home);
    session->interactive = interactive;
    session->last_status = 0;
    return 0;
}

int tdsh_session_clone(tdsh_session_t *dst,
                       const tdsh_session_t *src,
                       bool interactive)
{
    if (!dst || !src)
        return -EINVAL;
    memcpy(dst, src, sizeof(*dst));
    dst->interactive = interactive;
    dst->logout_requested = false;
    dst->script_runtime = NULL;
    return 0;
}

int tdsh_register_command(const tdsh_command_t *command)
{
    if (!s_core.initialized || !command || !command->name || !command->name[0] ||
        !command->usage || !command->help || !command->fn)
    {
        return -EINVAL;
    }
    if (s_core.command_count >= TDSH_MAX_COMMANDS)
        return -ENOSPC;
    for (size_t i = 0; i < s_core.command_count; ++i)
    {
        if (strcmp(s_core.commands[i].name, command->name) == 0)
            return -EEXIST;
    }
    s_core.commands[s_core.command_count++] = *command;
    return 0;
}

int tdsh_register_commands(const tdsh_command_t *commands, size_t count)
{
    if (!commands && count)
        return -EINVAL;
    for (size_t i = 0; i < count; ++i)
    {
        int rc = tdsh_register_command(&commands[i]);
        if (rc != 0)
            return rc;
    }
    return 0;
}

const tdsh_command_t *tdsh_commands_get(size_t *count)
{
    if (count)
        *count = s_core.command_count;
    return s_core.commands;
}

const tdsh_command_t *tdsh_command_find(const char *name)
{
    if (!name)
        return NULL;
    for (size_t i = 0; i < s_core.command_count; ++i)
    {
        if (strcmp(s_core.commands[i].name, name) == 0)
            return &s_core.commands[i];
    }
    return NULL;
}

int tdsh_execute_argv(tdsh_session_t *session, int argc, char **argv)
{
    if (!session || argc <= 0 || !argv || !argv[0])
        return 0;
    if(!tdsh_session_valid(session)){
        session->logout_requested=true;
        printf("tdsh: session expired; sign in again\n");return 126;
    }
    const tdsh_command_t *cmd = tdsh_command_find(argv[0]);
    if (!cmd)
    {
        printf("tdsh: command not found: %s\n", argv[0]);
        return 127;
    }
    if ((cmd->flags & TDSH_CMD_ADMIN_ONLY) &&
        (tdsh_session_role(session)<TDSH_ROLE_ADMIN||!tdsh_session_has_right(session,TDSH_RIGHT_USERS)))
    {
        printf("tdsh: permission denied: account administrator required\n");return 126;
    }
    if((cmd->flags>>8)&&!tdsh_session_has_right(session,cmd->flags>>8))
    {
        printf("tdsh: permission denied: account right required\n");return 126;
    }
    if ((cmd->flags & TDSH_CMD_ROOT_ONLY) != 0 &&
        strcmp(session->username, "root") != 0)
    {
        printf("tdsh: permission denied: root required\n");
        return 126;
    }
    if ((cmd->flags & TDSH_CMD_INTERACTIVE) != 0 && !session->interactive)
    {
        printf("tdsh: command requires an interactive terminal: %s\n", cmd->name);
        return 126;
    }
    return cmd->fn(session, argc, argv);
}

static bool protected_var(const char *name)
{
    return strcmp(name, "USER") == 0 || strcmp(name, "HOME") == 0 ||
           strcmp(name, "PWD") == 0 || strcmp(name, "HOSTNAME") == 0;
}

const char *tdsh_var_get(tdsh_session_t *session, const char *name)
{
    if (!session || !name)
        return NULL;
    if (strcmp(name, "USER") == 0)
        return session->username;
    if (strcmp(name, "HOME") == 0)
        return session->home;
    if (strcmp(name, "PWD") == 0)
        return session->cwd;
    if (strcmp(name, "HOSTNAME") == 0)
        return session->hostname;

    for (size_t i = 0; i < TDSH_MAX_VARS; ++i)
    {
        if (session->vars[i].used && strcmp(session->vars[i].name, name) == 0)
        {
            return session->vars[i].value;
        }
    }
    return NULL;
}

int tdsh_var_set(tdsh_session_t *session, const char *name, const char *value)
{
    if (!session || !name || !value || name[0] == '\0')
        return -EINVAL;
    if (protected_var(name))
        return -EPERM;
    if (strlen(name) >= TDSH_VAR_NAME_MAX || strlen(value) >= TDSH_VAR_VALUE_MAX)
    {
        return -ENOSPC;
    }

    tdsh_var_t *free_slot = NULL;
    for (size_t i = 0; i < TDSH_MAX_VARS; ++i)
    {
        if (session->vars[i].used)
        {
            if (strcmp(session->vars[i].name, name) == 0)
            {
                snprintf(session->vars[i].value, sizeof(session->vars[i].value), "%s", value);
                return 0;
            }
        }
        else if (!free_slot)
        {
            free_slot = &session->vars[i];
        }
    }

    if (!free_slot)
        return -ENOSPC;
    memset(free_slot, 0, sizeof(*free_slot));
    free_slot->used = true;
    snprintf(free_slot->name, sizeof(free_slot->name), "%s", name);
    snprintf(free_slot->value, sizeof(free_slot->value), "%s", value);
    return 0;
}

int tdsh_var_unset(tdsh_session_t *session, const char *name)
{
    if (!session || !name)
        return -EINVAL;
    if (protected_var(name))
        return -EPERM;
    for (size_t i = 0; i < TDSH_MAX_VARS; ++i)
    {
        if (session->vars[i].used && strcmp(session->vars[i].name, name) == 0)
        {
            memset(&session->vars[i], 0, sizeof(session->vars[i]));
            return 0;
        }
    }
    return -ENOENT;
}

uint64_t tdsh_monotonic_ms(void)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    return p && p->monotonic_ms ? p->monotonic_ms(p->context) : 0;
}

void tdsh_sleep_ms(uint32_t ms)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (p && p->sleep_ms)
        p->sleep_ms(p->context, ms);
}

void tdsh_yield(void)
{
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (p && p->yield)
        p->yield(p->context);
}

int tdsh_random_bytes(void *buffer, size_t length)
{
    if (!buffer && length)
        return -EINVAL;
    const tdsh_platform_api_t *p = s_core.cfg.platform;
    if (!p || !p->random_bytes)
        return -ENOSYS;
    return p->random_bytes(p->context, buffer, length);
}

void *tdsh_malloc(size_t size)
{
    if (size == 0)
        size = 1;
    if (size > SIZE_MAX - sizeof(tdsh_alloc_header_t))
    {
        atomic_fetch_add_explicit(&s_failed_allocations, 1, memory_order_relaxed);
        return NULL;
    }
    tdsh_alloc_header_t *h = raw_malloc(sizeof(*h) + size);
    if (!h)
    {
        atomic_fetch_add_explicit(&s_failed_allocations, 1, memory_order_relaxed);
        return NULL;
    }
    h->meta.size = size;
    h->meta.magic = TDSH_ALLOC_MAGIC;
    size_t blocks = atomic_fetch_add_explicit(&s_live_blocks, 1, memory_order_relaxed) + 1;
    size_t bytes = atomic_fetch_add_explicit(&s_live_bytes, size, memory_order_relaxed) + size;
    atomic_fetch_add_explicit(&s_total_allocations, 1, memory_order_relaxed);
    atomic_peak(&s_peak_blocks, blocks);
    atomic_peak(&s_peak_bytes, bytes);
    return (void *)(h + 1);
}

void *tdsh_calloc(size_t count, size_t size)
{
    if (count != 0 && size > SIZE_MAX / count)
    {
        atomic_fetch_add_explicit(&s_failed_allocations, 1, memory_order_relaxed);
        return NULL;
    }
    size_t total = count * size;
    void *p = tdsh_malloc(total);
    if (p)
        memset(p, 0, total);
    return p;
}

void *tdsh_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return tdsh_malloc(size);
    if (size == 0)
    {
        tdsh_free(ptr);
        return NULL;
    }
    if (size > SIZE_MAX - sizeof(tdsh_alloc_header_t))
        return NULL;

    tdsh_alloc_header_t *old = ((tdsh_alloc_header_t *)ptr) - 1;
    if (old->meta.magic != TDSH_ALLOC_MAGIC)
        return NULL;
    size_t old_size = old->meta.size;

    tdsh_alloc_header_t *h = raw_realloc(old, sizeof(*h) + size);
    if (!h)
    {
        atomic_fetch_add_explicit(&s_failed_allocations, 1, memory_order_relaxed);
        return NULL;
    }
    h->meta.size = size;
    h->meta.magic = TDSH_ALLOC_MAGIC;
    if (size > old_size)
    {
        size_t delta = size - old_size;
        size_t bytes = atomic_fetch_add_explicit(&s_live_bytes, delta, memory_order_relaxed) + delta;
        atomic_peak(&s_peak_bytes, bytes);
    }
    else if (old_size > size)
    {
        atomic_fetch_sub_explicit(&s_live_bytes, old_size - size, memory_order_relaxed);
    }
    return (void *)(h + 1);
}

void tdsh_free(void *ptr)
{
    if (!ptr)
        return;
    tdsh_alloc_header_t *h = ((tdsh_alloc_header_t *)ptr) - 1;
    if (h->meta.magic != TDSH_ALLOC_MAGIC)
    {
        /* Do not free an unknown pointer through the tracked allocator. */
        return;
    }
    size_t size = h->meta.size;
    h->meta.magic = 0;
    atomic_fetch_sub_explicit(&s_live_blocks, 1, memory_order_relaxed);
    atomic_fetch_sub_explicit(&s_live_bytes, size, memory_order_relaxed);
    raw_free(h);
}

char *tdsh_strdup(const char *text)
{
    if (!text)
        return NULL;
    size_t n = strlen(text) + 1;
    char *copy = tdsh_malloc(n);
    if (copy)
        memcpy(copy, text, n);
    return copy;
}

void tdsh_memory_get_stats(tdsh_memory_stats_t *stats)
{
    if (!stats)
        return;
    stats->live_blocks = atomic_load_explicit(&s_live_blocks, memory_order_relaxed);
    stats->live_bytes = atomic_load_explicit(&s_live_bytes, memory_order_relaxed);
    stats->peak_blocks = atomic_load_explicit(&s_peak_blocks, memory_order_relaxed);
    stats->peak_bytes = atomic_load_explicit(&s_peak_bytes, memory_order_relaxed);
    stats->total_allocations = atomic_load_explicit(&s_total_allocations, memory_order_relaxed);
    stats->failed_allocations = atomic_load_explicit(&s_failed_allocations, memory_order_relaxed);
}
