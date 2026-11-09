#include "tdsh_espidf_internal.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_attr.h"
#include "esp_heap_caps.h"
#include "esp_memory_utils.h"
#include "multi_heap.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/usb_serial_jtag.h"

#include <wolfssl/wolfcrypt/memory.h>
#include <wolfssl/wolfcrypt/asn_public.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include "nvs.h"
#include <wolfssh/ssh.h>
#include <wolfssh/log.h>
#include <wolfssh/wolfsftp.h>
#include "tdsh_sftp_jail.h"
#include "tdsh_ssh_hostkey.h"

#define TDSH_SSH_DEFAULT_PORT 22
#define TDSH_SSH_SERVER_STACK 18432
#define TDSH_SSH_MAX_CLIENTS  1
#define TDSH_SSH_SERVER_PRIO  4

/* Keep a red-zone after every wolfSSL allocation. If wolfSSL/wolfSSH writes a
 * little past the requested buffer, it damages this red-zone instead of the
 * ESP-IDF heap metadata immediately following the block. */
#define SSH_MEM_MAGIC        0x5353484Du /* 'SSHM' */
#define SSH_MEM_GUARD_BYTE   0xA5u
#define SSH_MEM_REDZONE_SIZE 64u
#define SSH_START_PENDING    (-1000)
#define C_RESET              "\033[0m"
#define C_GREEN              "\033[1;32m"
#define C_BLUE               "\033[1;34m"
#define C_CYAN               "\033[1;36m"
#define C_YELLOW             "\033[1;33m"

#ifdef DEBUG_WOLFSSH
/* wolfSSH v1.5.0 implements these in src/log.c but does not expose the
 * prototypes in log.h. Keep the declaration local to the debug build. */
extern void wolfSSH_Debugging_ON(void);
#endif

static const char *TAG = "tdsh-ssh";

/*
 * IMPORTANT: wolfSSH's default debug logger writes with fprintf(stdout,...).
 * During an interactive SSH shell this task deliberately redirects stdout and
 * stderr to ssh_stdio_write(). If wolfSSH_stream_send() logs while stdout is
 * redirected, the default logger recursively calls ssh_stdio_write() again:
 *
 *   wolfSSH_Log -> fprintf -> ssh_stdio_write -> wolfSSH_stream_send
 *       -> wolfSSH_Log -> fprintf -> ...
 *
 * Route wolfSSH diagnostics directly to USB Serial/JTAG instead. This bypasses Newlib
 * FILE streams completely, so debug logging remains safe even while the task's
 * stdin/stdout/stderr are attached to the encrypted SSH channel.
 */
#ifdef DEBUG_WOLFSSH
static const char *ssh_wolf_log_level(enum wolfSSH_LogLevel level)
{
    switch (level)
    {
    case WS_LOG_ERROR:
        return "ERROR";
    case WS_LOG_WARN:
        return "WARN";
    case WS_LOG_INFO:
        return "INFO";
    case WS_LOG_DEBUG:
        return "DEBUG";
    case WS_LOG_USER:
        return "USER";
    case WS_LOG_SFTP:
        return "SFTP";
    case WS_LOG_SCP:
        return "SCP";
    case WS_LOG_AGENT:
        return "AGENT";
    case WS_LOG_CERTMAN:
        return "CERTMAN";
    default:
        return "LOG";
    }
}

static void ssh_wolf_usb_log_cb(enum wolfSSH_LogLevel level,
                                const char *const msg)
{
    if (msg == NULL)
    {
        return;
    }

    char line[192];
    int n = snprintf(line, sizeof(line), "[wolfSSH][%s] %s\r\n",
                     ssh_wolf_log_level(level), msg);
    if (n <= 0)
    {
        return;
    }
    if (n >= (int)sizeof(line))
    {
        n = (int)sizeof(line) - 1;
    }

    /* Direct USB Serial/JTAG driver write: do NOT use printf/fprintf/ESP_LOG here. */
    (void)usb_serial_jtag_write_bytes(line, (size_t)n, 0);
}

#endif /* DEBUG_WOLFSSH */

typedef struct
{
    uint32_t magic;
    uint32_t size;
    uint32_t size_xor;
    uint32_t reserved;
} ssh_mem_hdr_t;

static WOLFSSH_CTX *s_ctx;
static TaskHandle_t s_server_task;
static int s_listen_fd = -1;
static int s_client_fd = -1;
static uint16_t s_port = TDSH_SSH_DEFAULT_PORT;
static volatile bool s_running;
static volatile int s_active_clients;
static volatile int s_start_result = SSH_START_PENDING;
static portMUX_TYPE s_lock = portMUX_INITIALIZER_UNLOCKED;
static bool s_wolfssh_initialized;
static bool s_allocators_installed;
static multi_heap_handle_t s_ssh_private_heap;
#define SSH_PRIVATE_HEAP_SIZE (64U * 1024U)
/* The arena is allocated on the first `ssh start` (not a static buffer, so
 * boards without PSRAM keep 64 KB of static RAM for everything else): from
 * PSRAM when the chip has it, else from internal RAM. It is kept afterwards,
 * because wolfSSL's allocator stays installed. */
static uint8_t *s_ssh_heap_arena;

/* Free internal RAM the server wants before it starts, besides the arena.
 * With the arena in PSRAM, internal RAM only has to hold the server and shell
 * task stacks (18 + 24 KB, internal because SFTP writes flash) and socket
 * buffers; with the arena in internal RAM more headroom is kept, as before. */
#define SSH_MIN_INTERNAL_FREE_PSRAM (64U * 1024U)
#define SSH_MIN_INTERNAL_FREE       (96U * 1024U)

/* Whether the arena is (or would be) in PSRAM. */
static bool ssh_arena_in_psram(void)
{
    if (s_ssh_heap_arena)
        return esp_ptr_external_ram(s_ssh_heap_arena);
#if CONFIG_SPIRAM
    return heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT) >= SSH_PRIVATE_HEAP_SIZE;
#else
    return false;
#endif
}

static const char *ssh_arena_where(void)
{
    return ssh_arena_in_psram() ? "PSRAM" : "internal";
}

/* Internal RAM needed before a start: the headroom, plus the arena itself if
 * it is still to be taken from internal RAM. */
static size_t ssh_internal_needed(void)
{
    bool psram = ssh_arena_in_psram();
    size_t need = psram ? SSH_MIN_INTERNAL_FREE_PSRAM : SSH_MIN_INTERNAL_FREE;
    if (!s_ssh_heap_arena && !psram)
        need += SSH_PRIVATE_HEAP_SIZE;
    return need;
}
static volatile uint32_t s_guard_errors;

/* -------------------------------------------------------------------------- */
/* wolfSSL / wolfCrypt allocator isolation                                    */
/* -------------------------------------------------------------------------- */

static bool ssh_mem_validate(void *ptr, bool log_error)
{
    if (ptr == NULL)
    {
        return true;
    }

    ssh_mem_hdr_t *hdr = ((ssh_mem_hdr_t *)ptr) - 1;
    if (hdr->magic != SSH_MEM_MAGIC || hdr->size_xor != (hdr->size ^ 0xFFFFFFFFu))
    {
        if (log_error)
        {
            ESP_LOGE(TAG, "wolfSSL allocator header corruption at %p", ptr);
        }
        s_guard_errors++;
        return false;
    }

    const uint8_t *tail = (const uint8_t *)ptr + hdr->size;
    for (size_t i = 0; i < SSH_MEM_REDZONE_SIZE; ++i)
    {
        if (tail[i] != SSH_MEM_GUARD_BYTE)
        {
            if (log_error)
            {
                ESP_LOGE(TAG,
                         "wolfSSL allocation overrun detected at %p: size=%u guard[%u]=0x%02X",
                         ptr, (unsigned)hdr->size, (unsigned)i, (unsigned)tail[i]);
            }
            s_guard_errors++;
            return false;
        }
    }
    return true;
}

static void *ssh_private_malloc(size_t size)
{
    if (size == 0)
        size = 1;
    if (!s_ssh_private_heap)
        return NULL;
    if (size > UINT32_MAX - sizeof(ssh_mem_hdr_t) - SSH_MEM_REDZONE_SIZE)
        return NULL;

    size_t total = sizeof(ssh_mem_hdr_t) + size + SSH_MEM_REDZONE_SIZE;
    ssh_mem_hdr_t *hdr = (ssh_mem_hdr_t *)multi_heap_malloc(s_ssh_private_heap, total);
    if (!hdr)
    {
        ESP_LOGE(TAG, "wolfSSL private heap exhausted: request=%u free=%u",
                 (unsigned)size,
                 (unsigned)multi_heap_free_size(s_ssh_private_heap));
        return NULL;
    }

    hdr->magic = SSH_MEM_MAGIC;
    hdr->size = (uint32_t)size;
    hdr->size_xor = hdr->size ^ 0xFFFFFFFFu;
    hdr->reserved = 0;
    void *user = (void *)(hdr + 1);
    memset((uint8_t *)user + size, SSH_MEM_GUARD_BYTE, SSH_MEM_REDZONE_SIZE);
    return user;
}

static void ssh_private_free(void *ptr)
{
    if (!ptr)
        return;
    ssh_mem_hdr_t *hdr = ((ssh_mem_hdr_t *)ptr) - 1;
    if (hdr->magic != SSH_MEM_MAGIC || hdr->size_xor != (hdr->size ^ 0xFFFFFFFFu))
    {
        ESP_LOGE(TAG, "wolfSSL free refused: invalid allocator header at %p", ptr);
        s_guard_errors++;
        return;
    }
    (void)ssh_mem_validate(ptr, true);
    hdr->magic = 0;
    multi_heap_free(s_ssh_private_heap, hdr);
}

static void *ssh_private_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return ssh_private_malloc(size);
    if (size == 0)
    {
        ssh_private_free(ptr);
        return NULL;
    }

    ssh_mem_hdr_t *old_hdr = ((ssh_mem_hdr_t *)ptr) - 1;
    if (old_hdr->magic != SSH_MEM_MAGIC ||
        old_hdr->size_xor != (old_hdr->size ^ 0xFFFFFFFFu))
    {
        ESP_LOGE(TAG, "wolfSSL realloc refused: invalid allocator header at %p", ptr);
        s_guard_errors++;
        return NULL;
    }

    (void)ssh_mem_validate(ptr, true);
    size_t old_size = old_hdr->size;
    void *next = ssh_private_malloc(size);
    if (!next)
        return NULL;
    memcpy(next, ptr, old_size < size ? old_size : size);
    ssh_private_free(ptr);
    return next;
}

static int ssh_install_allocators(void)
{
    if (s_allocators_installed)
        return 0;

    if (!s_ssh_heap_arena)
    {
#if CONFIG_SPIRAM
        s_ssh_heap_arena = heap_caps_aligned_alloc(16, SSH_PRIVATE_HEAP_SIZE, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
#endif
        if (!s_ssh_heap_arena)
            s_ssh_heap_arena = heap_caps_aligned_alloc(16, SSH_PRIVATE_HEAP_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
        if (!s_ssh_heap_arena)
        {
            ESP_LOGE(TAG, "no %u bytes for the private SSH heap", (unsigned)SSH_PRIVATE_HEAP_SIZE);
            return -1;
        }
    }
    s_ssh_private_heap = multi_heap_register(s_ssh_heap_arena, SSH_PRIVATE_HEAP_SIZE);
    if (!s_ssh_private_heap)
    {
        ESP_LOGE(TAG, "failed to register %u-byte private SSH heap",
                 (unsigned)SSH_PRIVATE_HEAP_SIZE);
        return -1;
    }

    int rc = wolfSSL_SetAllocators(
        (wolfSSL_Malloc_cb)ssh_private_malloc,
        (wolfSSL_Free_cb)ssh_private_free,
        (wolfSSL_Realloc_cb)ssh_private_realloc);
    if (rc != 0)
    {
        ESP_LOGE(TAG, "wolfSSL_SetAllocators failed: %d", rc);
        return -1;
    }

    s_allocators_installed = true;
    ESP_LOGI(TAG, "wolfSSL allocator isolated to private %s heap: size=%u free=%u",
             ssh_arena_where(), (unsigned)SSH_PRIVATE_HEAP_SIZE,
             (unsigned)multi_heap_free_size(s_ssh_private_heap));
    return 0;
}

static void ssh_heap_stats(const char *stage)
{
    unsigned private_free = s_ssh_private_heap
                                ? (unsigned)multi_heap_free_size(s_ssh_private_heap)
                                : 0U;
    ESP_LOGI(TAG,
             "%s: internal free=%u largest=%u | SSH private free=%u/%u | guard_errors=%u",
             stage,
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
             (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT),
             private_free,
             (unsigned)SSH_PRIVATE_HEAP_SIZE,
             (unsigned)s_guard_errors);
}

/* -------------------------------------------------------------------------- */
/* Authentication                                                             */
/* -------------------------------------------------------------------------- */

static void client_count_add(int delta)
{
    portENTER_CRITICAL(&s_lock);
    s_active_clients += delta;
    portEXIT_CRITICAL(&s_lock);
}

static int client_count_get(void)
{
    int n;
    portENTER_CRITICAL(&s_lock);
    n = s_active_clients;
    portEXIT_CRITICAL(&s_lock);
    return n;
}

/* The client's terminal width from its pty request (0: none yet). One SSH
 * client at a time, so one value. The build does not handle window-change
 * requests (no WOLFSSH_SHELL), so a resize takes effect at the next login. */
static volatile int s_pty_columns;

static int ssh_terminal_size(WOLFSSH *ssh, word32 columns, word32 rows,
                             word32 width_px, word32 height_px, void *ctx)
{
    (void)ssh;
    (void)rows;
    (void)width_px;
    (void)height_px;
    (void)ctx;
    s_pty_columns = columns > 0U && columns < 10000U ? (int)columns : 0;
    return WS_SUCCESS;
}

int tdsh_ssh_terminal_columns(void)
{
    return s_pty_columns;
}

static int ssh_user_auth(byte authType, WS_UserAuthData *authData, void *ctx)
{
    (void)ctx;

    if (authType != WOLFSSH_USERAUTH_PASSWORD)
    {
        return WOLFSSH_USERAUTH_INVALID_AUTHTYPE;
    }
    if (authData == NULL || authData->username == NULL ||
        authData->sf.password.password == NULL)
    {
        return WOLFSSH_USERAUTH_FAILURE;
    }
    if (authData->usernameSz == 0 || authData->usernameSz >= TDSH_USERNAME_MAX ||
        authData->sf.password.passwordSz >= 128U)
    {
        return WOLFSSH_USERAUTH_FAILURE;
    }

    char user[TDSH_USERNAME_MAX];
    char pass[128];
    memcpy(user, authData->username, authData->usernameSz);
    user[authData->usernameSz] = '\0';
    memcpy(pass, authData->sf.password.password, authData->sf.password.passwordSz);
    pass[authData->sf.password.passwordSz] = '\0';

    const bool ok = tdsh_user_authenticate_remote(user, pass);
    memset(pass, 0, sizeof(pass));

    if (!ok)
    {
        return tdsh_user_exists(user) ? WOLFSSH_USERAUTH_INVALID_PASSWORD
                                      : WOLFSSH_USERAUTH_INVALID_USER;
    }
    return WOLFSSH_USERAUTH_SUCCESS;
}

static int ssh_user_auth_types(WOLFSSH *ssh, void *ctx)
{
    (void)ssh;
    (void)ctx;
    return WOLFSSH_USERAUTH_PASSWORD;
}

/* the SFTP start directory used to be set in wolfSSH's
 * user-auth *result* callback, which wolfSSH only calls for public-key
 * logins. Password logins therefore started in "/", which ESP-IDF cannot
 * list ("Unable To Open Directory" in FileZilla). It is now set in
 * ssh_handle_client() right before the SFTP loop, for every login. */

/* -------------------------------------------------------------------------- */
/* SSH-backed stdio                                                           */
/* -------------------------------------------------------------------------- */

/* The SSH shell session's connection and task, for tdsh_ssh_break_requested
 * (one SSH client at a time). */
static WOLFSSH *volatile s_shell_ssh;
static TaskHandle_t volatile s_shell_task;

bool tdsh_ssh_break_requested(void)
{
    WOLFSSH *ssh = s_shell_ssh;
    if (!ssh || xTaskGetCurrentTaskHandle() != s_shell_task)
        return false;
    /* Take in what the client sent (one packet per check, without waiting),
     * then look at the session's input without consuming it. */
    int fd = (int)wolfSSH_get_fd(ssh);
    fd_set readable;
    FD_ZERO(&readable);
    FD_SET(fd, &readable);
    struct timeval tv = {0};
    if (select(fd + 1, &readable, NULL, NULL, &tv) > 0)
        (void)wolfSSH_worker(ssh, NULL);
    byte buf[64];
    int n = wolfSSH_stream_peek(ssh, buf, sizeof(buf));
    for (int i = n - 1; i >= 0; i--)
        if (buf[i] == 0x03)
        {
            /* Drop the input up to and including it, like a terminal. */
            (void)wolfSSH_stream_read(ssh, buf, (word32)i + 1U);
            return true;
        }
    return false;
}

static int ssh_stdio_read(void *cookie, char *buf, int len)
{
    WOLFSSH *ssh = (WOLFSSH *)cookie;
    if (!ssh || !buf || len <= 0)
        return -1;

    int ret = wolfSSH_stream_read(ssh, (byte *)buf, (word32)len);
    if (ret > 0)
        return ret;

    int err = wolfSSH_get_error(ssh);
    if (err == WS_EOF || ret == WS_CHANNEL_CLOSED)
        return 0;
    return -1;
}

/*
 * SSH PTY output is a terminal byte stream, not a Unix text file.
 * Most tdsh commands use '\n'. On a VT/xterm terminal LF moves down one
 * row but does not necessarily return to column zero, so the next prompt can
 * appear indented. Convert a lone LF to CRLF while preserving an existing
 * CRLF sequence.
 *
 * There is only one SSH client at a time in this server, so one small piece
 * of state is sufficient even when stdio splits "\r" and "\n" across two
 * separate write callbacks.
 */
static bool s_ssh_stdio_prev_was_cr = false;

static int ssh_stream_send_all(WOLFSSH *ssh, const byte *data, word32 len)
{
    word32 sent = 0;

    while (sent < len)
    {
        int ret = wolfSSH_stream_send(ssh, (byte *)(data + sent), len - sent);
        if (ret <= 0)
        {
            return -1;
        }
        sent += (word32)ret;
    }

    return 0;
}

static int ssh_stdio_write(void *cookie, const char *buf, int len)
{
    WOLFSSH *ssh = (WOLFSSH *)cookie;
    if (!ssh || !buf || len <= 0)
        return -1;

    byte out[256];
    size_t out_len = 0;

    for (int i = 0; i < len; ++i)
    {
        const unsigned char ch = (unsigned char)buf[i];

        /* Worst case for one input byte is two output bytes (CR + LF). */
        if (out_len > sizeof(out) - 2U)
        {
            if (ssh_stream_send_all(ssh, out, (word32)out_len) != 0)
            {
                return -1;
            }
            out_len = 0;
        }

        if (ch == '\n')
        {
            if (!s_ssh_stdio_prev_was_cr)
            {
                out[out_len++] = '\r';
            }
            out[out_len++] = '\n';
            s_ssh_stdio_prev_was_cr = false;
        }
        else
        {
            out[out_len++] = ch;
            s_ssh_stdio_prev_was_cr = (ch == '\r');
        }
    }

    if (out_len > 0 &&
        ssh_stream_send_all(ssh, out, (word32)out_len) != 0)
    {
        return -1;
    }

    /* funopen write callbacks return input bytes consumed, not wire bytes. */
    return len;
}

static void ssh_prompt(const tdsh_session_t *s, char *out, size_t out_sz)
{
    const char *shown = s->cwd;
    char short_path[TDSH_MAX_PATH + 4];

    if (strcmp(s->cwd, s->home) == 0)
    {
        shown = "~";
    }
    else if (strncmp(s->cwd, s->home, strlen(s->home)) == 0 &&
             s->cwd[strlen(s->home)] == '/')
    {
        snprintf(short_path, sizeof(short_path), "~%s", s->cwd + strlen(s->home));
        shown = short_path;
    }

    char venv[TDSH_VAR_VALUE_MAX + 4];   /* "(name) " while a venv is active */
    tdsh_prompt_prefix((tdsh_session_t *)s, venv, sizeof(venv));
    snprintf(out, out_sz, "%s" C_GREEN "%s@%s" C_RESET ":" C_BLUE "%s" C_RESET "%c ",
             venv, s->username, s->hostname, shown,
             strcmp(s->username, "root") == 0 ? '#' : '$');
}

static int run_ssh_shell(WOLFSSH *ssh)
{
    const char *user = wolfSSH_GetUsername(ssh);
    if (!user || !tdsh_user_exists(user))
        return 1;

    tdsh_session_t *session = (tdsh_session_t *)heap_caps_calloc(
        1, sizeof(*session), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!session)
    {
        ESP_LOGE(TAG, "cannot allocate SSH shell session in internal RAM");
        return 1;
    }

    if (tdsh_session_init(session, user, true) != 0 ||
        tdsh_session_set_user(session, user) != 0)
    {
        heap_caps_free(session);
        return 1;
    }

    FILE *old_in = stdin;
    FILE *old_out = stdout;
    FILE *old_err = stderr;

    /* New SSH terminal session: do not inherit CR/LF state from an old one. */
    s_ssh_stdio_prev_was_cr = false;

    FILE *io = funopen(ssh, ssh_stdio_read, ssh_stdio_write, NULL, NULL);
    if (!io)
    {
        heap_caps_free(session);
        return 1;
    }
    setvbuf(io, NULL, _IONBF, 0);
    stdin = io;
    stdout = io;
    stderr = io;
    s_shell_task = xTaskGetCurrentTaskHandle();
    s_shell_ssh = ssh;

    printf("\r\n==========================================\r\n");
    printf("          WELCOME TO TINYDESK SHELL\r\n");
    printf("              Version %s\r\n", TDSH_VERSION);
    printf("                   SSH\r\n");
    printf("==========================================\r\n\r\n");
    printf("Type 'help' to list commands. Type 'exit' to disconnect.\r\n\r\n");

    WS_SessionType type = wolfSSH_GetSessionType(ssh);
    int rc = 0;
    if (type == WOLFSSH_SESSION_EXEC)
    {
        const char *cmd = wolfSSH_GetSessionCommand(ssh);
        if (cmd && cmd[0])
            rc = tdsh_execute_line(session, cmd);
        (void)wolfSSH_stream_exit(ssh, rc);
    }
    else
    {
        if (!session->logout_requested)
            for (;;)
            {
                char prompt[TDSH_MAX_PATH + 96], line[TDSH_MAX_LINE + 1];
                ssh_prompt(session, prompt, sizeof(prompt));
                int n = tdsh_interactive_readline(session, prompt, line, sizeof(line));
                if (n < 0)
                    break;
                if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0)
                    break;
                if (n > 0)
                {
                    rc = tdsh_execute_line(session, line);
                    if (session->logout_requested)
                        break;
                }
            }
    }

    s_shell_ssh = NULL;
    s_shell_task = NULL;
    fflush(io);
    stdin = old_in;
    stdout = old_out;
    stderr = old_err;
    fclose(io);
    heap_caps_free(session);
    return rc;
}

static int wait_socket(int fd, bool want_write, int timeout_ms)
{
    fd_set rfds, wfds;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    if (want_write)
        FD_SET(fd, &wfds);
    else
        FD_SET(fd, &rfds);
    struct timeval tv = {
        .tv_sec = timeout_ms / 1000,
        .tv_usec = (timeout_ms % 1000) * 1000,
    };
    return select(fd + 1, want_write ? NULL : &rfds,
                  want_write ? &wfds : NULL, NULL, &tv);
}

static int run_sftp(WOLFSSH *ssh)
{
#ifndef WOLFSSH_SFTP
    (void)ssh;
    return WS_FATAL_ERROR;
#else
    int fd = (int)wolfSSH_get_fd(ssh);
    int ret = wolfSSH_get_error(ssh);

    for (;;)
    {
        int err = wolfSSH_get_error(ssh);
        if (ret == WS_WANT_WRITE || ret == WS_CHAN_RXD ||
            wolfSSH_SFTP_PendingSend(ssh))
        {
            ret = wolfSSH_SFTP_read(ssh);
            err = wolfSSH_get_error(ssh);
            if (err == WS_EOF)
                return WS_SUCCESS;
            if (err == WS_WANT_WRITE || wolfSSH_SFTP_PendingSend(ssh))
                continue;
        }

        bool want_write = (err == WS_WANT_WRITE);
        int sel = wait_socket(fd, want_write, 1000);
        if (sel < 0)
            return WS_FATAL_ERROR;
        if (sel == 0)
        {
            if (!s_running)
                return WS_SUCCESS;
            continue;
        }

        ret = wolfSSH_worker(ssh, NULL);
        err = wolfSSH_get_error(ssh);
        if (ret == WS_CHAN_RXD || err == WS_CHAN_RXD ||
            err == WS_WANT_WRITE || wolfSSH_SFTP_PendingSend(ssh))
        {
            continue;
        }
        if (err == WS_EOF || ret == WS_CHANNEL_CLOSED)
            return WS_SUCCESS;
        if (ret < 0 && err != WS_WANT_READ && err != WS_WANT_WRITE &&
            err != WS_REKEYING && err != WS_WINDOW_FULL)
        {
            return ret;
        }
    }
#endif
}

/* -------------------------------------------------------------------------- */
/* Client/server                                                              */
/* -------------------------------------------------------------------------- */

static void ssh_shutdown_client_fd(void)
{
    int fd = -1;
    portENTER_CRITICAL(&s_lock);
    fd = s_client_fd;
    portEXIT_CRITICAL(&s_lock);
    if (fd >= 0)
    {
        shutdown(fd, SHUT_RDWR);
    }
}

static void ssh_handle_client(int fd, const struct sockaddr_in *peer)
{
    char ip[INET_ADDRSTRLEN] = {0};
    if (peer != NULL)
    {
        (void)inet_ntop(AF_INET, &peer->sin_addr, ip, sizeof(ip));
    }

    client_count_add(1);
    portENTER_CRITICAL(&s_lock);
    s_client_fd = fd;
    portEXIT_CRITICAL(&s_lock);

    ESP_LOGI(TAG, "SSH client connected from %s", ip[0] ? ip : "unknown");
    ssh_heap_stats("before wolfSSH_new");

    WOLFSSH *ssh = wolfSSH_new(s_ctx);
    if (!ssh)
    {
        ESP_LOGE(TAG, "wolfSSH_new failed");
        goto done;
    }

    wolfSSH_set_fd(ssh, fd);
    wolfSSH_SetUserAuthCtx(ssh, ssh);
    s_pty_columns = 0;
    wolfSSH_SetTerminalResizeCb(ssh, ssh_terminal_size);

    int ret = wolfSSH_accept(ssh);
    if (ret == WS_SFTP_COMPLETE)
    {
        /* every user may use SFTP; anyone but root is kept
         * inside their home by the jail in wolfssh_local/sftp_jail.c. */
        const char *user = wolfSSH_GetUsername(ssh);
        if (user == NULL || !tdsh_user_exists(user))
        {
            ESP_LOGW(TAG, "SFTP denied for unknown user %s", user ? user : "unknown");
        }
        else
        {
            char home[TDSH_MAX_PATH + sizeof(TDSH_MOUNT_POINT) + 8];
            bool is_root = strcmp(user, "root") == 0;
            if (is_root)
                snprintf(home, sizeof(home), "%s/root", TDSH_MOUNT_POINT);
            else
                snprintf(home, sizeof(home), "%s/home/%s", TDSH_MOUNT_POINT, user);
            (void)mkdir(home, 0755);                  /* first login: no home yet */
            (void)wolfSSH_SFTP_SetDefaultPath(ssh, home);
            tdsh_sftp_jail_enter(is_root ? NULL : home);
            ESP_LOGI(TAG, "SFTP authenticated as %s%s", user, is_root ? "" : " (confined to home)");
            (void)run_sftp(ssh);
            tdsh_sftp_jail_leave();
        }
    }
    else if (ret == WS_SUCCESS)
    {
        ESP_LOGI(TAG, "SSH shell authenticated as %s", wolfSSH_GetUsername(ssh));
        (void)run_ssh_shell(ssh);
    }
    else
    {
        ESP_LOGW(TAG, "wolfSSH_accept failed: %d (%s)", ret,
                 wolfSSH_ErrorToName(wolfSSH_get_error(ssh)));
    }

    (void)wolfSSH_shutdown(ssh);
    wolfSSH_free(ssh);
    ssh_heap_stats("after wolfSSH_free");

done:
    shutdown(fd, SHUT_RDWR);
    close(fd);

    portENTER_CRITICAL(&s_lock);
    if (s_client_fd == fd)
        s_client_fd = -1;
    portEXIT_CRITICAL(&s_lock);

    client_count_add(-1);
    ESP_LOGI(TAG, "SSH client disconnected; server min stack=%u bytes",
             (unsigned)uxTaskGetStackHighWaterMark(NULL));
}

/* -------------------------------------------------------------------------- */
/* Host key                                                  */
/* -------------------------------------------------------------------------- */

/* Each device makes its own ECDSA P-256 host key the first time the server
 * starts (the network is up then, so the RF-seeded hardware RNG is ready)
 * and keeps it in NVS. The built-in development key in tdsh_ssh_hostkey.h
 * is only a fallback if that fails. "ssh hostkey new" (root) deletes the
 * stored key; the next start makes a new one. */
#define HOSTKEY_NVS_NS  "tdsh_ssh"
#define HOSTKEY_NVS_KEY "hostkey"
#define HOSTKEY_DER_MAX 160          /* a SEC1 P-256 key with its public part is 121 bytes */

static char s_hostkey_fp[56];        /* OpenSSH style: "SHA256:" + 43 base64 characters */
static const char *s_hostkey_kind;   /* NULL until the server has loaded a key */

static void wipe(void *buf, size_t len)
{
    volatile uint8_t *p = (volatile uint8_t *)buf;
    while (len--)
        *p++ = 0;
}

static bool hostkey_load(uint8_t *der, size_t *len)
{
    nvs_handle_t h;
    if (nvs_open(HOSTKEY_NVS_NS, NVS_READONLY, &h) != ESP_OK)
        return false;
    esp_err_t err = nvs_get_blob(h, HOSTKEY_NVS_KEY, der, len);
    nvs_close(h);
    return err == ESP_OK && *len > 0;
}

static bool hostkey_save(const uint8_t *der, size_t len)
{
    nvs_handle_t h;
    if (nvs_open(HOSTKEY_NVS_NS, NVS_READWRITE, &h) != ESP_OK)
        return false;
    esp_err_t err = nvs_set_blob(h, HOSTKEY_NVS_KEY, der, len);
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err == ESP_OK;
}

static bool hostkey_erase(void)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(HOSTKEY_NVS_NS, NVS_READWRITE, &h);
    if (err == ESP_ERR_NVS_NOT_FOUND)
        return true;          /* never stored */
    if (err != ESP_OK)
        return false;
    err = nvs_erase_key(h, HOSTKEY_NVS_KEY);
    if (err == ESP_ERR_NVS_NOT_FOUND)
        err = ESP_OK;
    if (err == ESP_OK)
        err = nvs_commit(h);
    nvs_close(h);
    return err == ESP_OK;
}

/* DER length of a new key, or < 0. */
static int hostkey_generate(uint8_t *der, word32 cap)
{
    int ret = -1;
    WC_RNG *rng = wc_rng_new(NULL, 0, NULL);
    ecc_key *key = wc_ecc_key_new(NULL);
    if (rng && key && wc_ecc_make_key_ex(rng, 32, key, ECC_SECP256R1) == 0)
        ret = wc_EccKeyToDer(key, der, cap);
    if (key)
        wc_ecc_key_free(key);
    if (rng)
        wc_rng_free(rng);
    return ret;
}

static void base64_nopad(const uint8_t *in, size_t n, char *out)
{
    static const char T[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i = 0;
    for (; i + 2 < n; i += 3)
    {
        uint32_t v = ((uint32_t)in[i] << 16) | ((uint32_t)in[i + 1] << 8) | in[i + 2];
        *out++ = T[(v >> 18) & 63];
        *out++ = T[(v >> 12) & 63];
        *out++ = T[(v >> 6) & 63];
        *out++ = T[v & 63];
    }
    if (n - i >= 1)
    {
        uint32_t v = ((uint32_t)in[i] << 16) | (n - i == 2 ? (uint32_t)in[i + 1] << 8 : 0);
        *out++ = T[(v >> 18) & 63];
        *out++ = T[(v >> 12) & 63];
        if (n - i == 2)
            *out++ = T[(v >> 6) & 63];
    }
    *out = '\0';
}

static uint8_t *put_string(uint8_t *p, const void *data, uint32_t len)
{
    p[0] = (uint8_t)(len >> 24);
    p[1] = (uint8_t)(len >> 16);
    p[2] = (uint8_t)(len >> 8);
    p[3] = (uint8_t)len;
    memcpy(p + 4, data, len);
    return p + 4 + len;
}

/* The fingerprint clients show: SHA-256 of the SSH public key blob. */
static void hostkey_fingerprint(const uint8_t *der, word32 len)
{
    s_hostkey_fp[0] = '\0';
    ecc_key *key = wc_ecc_key_new(NULL);
    if (!key)
        return;
    uint8_t point[65];
    word32 plen = sizeof(point), idx = 0;
    if (wc_EccPrivateKeyDecode(der, &idx, key, len) == 0 && wc_ecc_export_x963(key, point, &plen) == 0 &&
        plen == sizeof(point))
    {
        uint8_t blob[4 + 19 + 4 + 8 + 4 + 65];
        uint8_t *p = put_string(blob, "ecdsa-sha2-nistp256", 19);
        p = put_string(p, "nistp256", 8);
        put_string(p, point, sizeof(point));
        wc_Sha256 sha;
        uint8_t digest[WC_SHA256_DIGEST_SIZE];
        if (wc_InitSha256(&sha) == 0)
        {
            if (wc_Sha256Update(&sha, blob, sizeof(blob)) == 0 && wc_Sha256Final(&sha, digest) == 0)
            {
                memcpy(s_hostkey_fp, "SHA256:", 7);
                base64_nopad(digest, sizeof(digest), s_hostkey_fp + 7);
            }
            wc_Sha256Free(&sha);
        }
    }
    wc_ecc_key_free(key);
}

/* Load this device's host key into s_ctx (making it on first use). */
static int ssh_use_host_key(void)
{
    uint8_t der[HOSTKEY_DER_MAX];
    size_t der_len = sizeof(der);
    bool stored = hostkey_load(der, &der_len);
    int ret = WS_FATAL_ERROR;

    if (stored)
    {
        ret = wolfSSH_CTX_UsePrivateKey_buffer(s_ctx, der, (word32)der_len, WOLFSSH_FORMAT_ASN1);
        if (ret != WS_SUCCESS)
            ESP_LOGE(TAG, "stored host key is unusable (%d); making a new one", ret);
    }
    if (ret != WS_SUCCESS)
    {
        ESP_LOGI(TAG, "SSH init stage: generating this device's host key");
        int n = hostkey_generate(der, sizeof(der));
        if (n > 0)
        {
            der_len = (size_t)n;
            ret = wolfSSH_CTX_UsePrivateKey_buffer(s_ctx, der, (word32)der_len, WOLFSSH_FORMAT_ASN1);
            if (ret == WS_SUCCESS && !hostkey_save(der, der_len))
                ESP_LOGW(TAG, "could not store the new host key; it lasts until the next restart");
        }
        else
        {
            ESP_LOGE(TAG, "host key generation failed: %d", n);
        }
    }
    if (ret == WS_SUCCESS)
    {
        hostkey_fingerprint(der, (word32)der_len);
        s_hostkey_kind = "per-device ECDSA P-256";
    }
    wipe(der, sizeof(der));
    if (ret == WS_SUCCESS)
        return ret;

    ESP_LOGE(TAG, "using the built-in development host key");
    ret = wolfSSH_CTX_UsePrivateKey_buffer(s_ctx, (const byte *)tdsh_ssh_host_key_der,
                                           (word32)tdsh_ssh_host_key_der_len, WOLFSSH_FORMAT_ASN1);
    if (ret == WS_SUCCESS)
    {
        hostkey_fingerprint(tdsh_ssh_host_key_der, (word32)tdsh_ssh_host_key_der_len);
        s_hostkey_kind = "built-in development key (not unique!)";
    }
    return ret;
}

static int ssh_prepare_server_context(void)
{
    ssh_heap_stats("SSH init: begin");

    if (ssh_install_allocators() != 0)
    {
        return -1;
    }

    if (!s_wolfssh_initialized)
    {
#ifdef DEBUG_WOLFSSH
        /* Install the non-stdio logger BEFORE enabling wolfSSH debug output. */
        wolfSSH_SetLoggingCb(ssh_wolf_usb_log_cb);
        wolfSSH_Debugging_ON();
        ESP_LOGI(TAG, "wolfSSH debug logging enabled (direct USB Serial/JTAG callback)");
#endif
        ESP_LOGI(TAG, "SSH init stage: wolfSSH_Init");
        if (wolfSSH_Init() != WS_SUCCESS)
        {
            ESP_LOGE(TAG, "wolfSSH_Init failed");
            return -1;
        }
        s_wolfssh_initialized = true;
    }

    ESP_LOGI(TAG, "SSH init stage: wolfSSH_CTX_new");
    s_ctx = wolfSSH_CTX_new(WOLFSSH_ENDPOINT_SERVER, NULL);
    if (!s_ctx)
    {
        ESP_LOGE(TAG, "wolfSSH_CTX_new failed");
        return -1;
    }

    ESP_LOGI(TAG, "SSH init stage: callbacks/banner");
    wolfSSH_SetUserAuth(s_ctx, ssh_user_auth);
    wolfSSH_SetUserAuthTypes(s_ctx, ssh_user_auth_types);
    (void)wolfSSH_CTX_SetBanner(s_ctx, "tdsh-idf SSH/SFTP\r\n");

    ESP_LOGI(TAG, "SSH init stage: host-key parse");
    int ret = ssh_use_host_key();
    if (ret != WS_SUCCESS)
    {
        ESP_LOGE(TAG, "unable to load ECDSA host key: %d", ret);
        wolfSSH_CTX_free(s_ctx);
        s_ctx = NULL;
        return -1;
    }

    ssh_heap_stats("SSH init: context ready");
    return 0;
}

static void ssh_server_task(void *arg)
{
    const uint16_t port = (uint16_t)(uintptr_t)arg;

    /* All wolfSSH context creation, use and destruction happens in THIS task.
     * This is important with SINGLE_THREADED wolfCrypt builds. */
    if (ssh_prepare_server_context() != 0)
    {
        s_start_result = 1;
        s_running = false;
        s_server_task = NULL;
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "SSH init stage: socket/bind/listen");
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (fd < 0)
    {
        ESP_LOGE(TAG, "socket failed: %s", strerror(errno));
        goto init_fail;
    }

    int one = 1;
    (void)setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = htonl(INADDR_ANY),
    };

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        ESP_LOGE(TAG, "bind(%u) failed: %s", (unsigned)port, strerror(errno));
        close(fd);
        goto init_fail;
    }
    if (listen(fd, TDSH_SSH_MAX_CLIENTS) != 0)
    {
        ESP_LOGE(TAG, "listen failed: %s", strerror(errno));
        close(fd);
        goto init_fail;
    }

    /* in lwIP, shutdown() does not wake a blocked accept(),
     * so "ssh stop" timed out and left this task (and its 18 KB stack)
     * waiting for the next client. A receive timeout makes accept() return
     * twice a second to look at s_running, as the FTP server does. */
    struct timeval accept_tv = {.tv_sec = 0, .tv_usec = 500000};
    (void)setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &accept_tv, sizeof(accept_tv));

    s_listen_fd = fd;
    s_port = port;
    s_start_result = 0;

    ssh_heap_stats("SSH server ready");
    ESP_LOGI(TAG, "SSH/SFTP listening on port %u", (unsigned)port);

    while (s_running)
    {
        struct sockaddr_in peer;
        socklen_t plen = sizeof(peer);
        int client = accept(fd, (struct sockaddr *)&peer, &plen);
        if (client < 0)
        {
            if (!s_running)
                break;
            if (errno != EAGAIN && errno != EWOULDBLOCK)
                vTaskDelay(pdMS_TO_TICKS(50));
            continue;
        }
        if (!s_running)
        {        /* stopped meanwhile */
            close(client);
            break;
        }
        int no_delay = 1;
        if (setsockopt(client, IPPROTO_TCP, TCP_NODELAY, &no_delay, sizeof(no_delay)) != 0)
            ESP_LOGW(TAG, "TCP_NODELAY failed: %s", strerror(errno));
        ssh_handle_client(client, &peer);
    }

    shutdown(fd, SHUT_RDWR);
    close(fd);
    s_listen_fd = -1;

    if (s_ctx != NULL)
    {
        wolfSSH_CTX_free(s_ctx);
        s_ctx = NULL;
    }

    ssh_heap_stats("SSH server stopped");
    s_server_task = NULL;
    vTaskDelete(NULL);
    return;

init_fail:
    if (s_ctx != NULL)
    {
        wolfSSH_CTX_free(s_ctx);
        s_ctx = NULL;
    }
    s_start_result = 1;
    s_running = false;
    s_server_task = NULL;
    vTaskDelete(NULL);
}

static int ssh_start(uint16_t port)
{
    if (!tdsh_remote_access_ready())
    {
        printf("ssh: change the factory root password with passwd first (old password: " TDSH_FACTORY_ROOT_PASSWORD ")\n");
        return 1;
    }
    if (s_running)
    {
        printf("SSH server already running on port %u.\n", (unsigned)s_port);
        return 0;
    }
    if (s_server_task != NULL || s_ctx != NULL || client_count_get() != 0)
    {
        printf("ssh: previous server is still shutting down.\n");
        return 1;
    }
    if (!tdsh_network_is_reachable())
    {
        printf("ssh: no network interface is connected.\n");
        return 1;
    }
    size_t internal_free = heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    size_t internal_needed = ssh_internal_needed();
    if (internal_free < internal_needed)
    {
        printf("ssh: insufficient internal RAM (%u bytes free; need at least %u before start).\n",
               (unsigned)internal_free, (unsigned)internal_needed);
        return 1;
    }

    ssh_heap_stats("before SSH server task creation");

    s_port = port;
    s_start_result = SSH_START_PENDING;
    s_running = true;

    if (xTaskCreate(ssh_server_task,
                    "tdsh_sshd",
                    TDSH_SSH_SERVER_STACK,
                    (void *)(uintptr_t)port,
                    TDSH_SSH_SERVER_PRIO,
                    &s_server_task) != pdPASS)
    {
        s_running = false;
        s_server_task = NULL;
        printf("ssh: cannot create SSH server task.\n");
        return 1;
    }

    /* Wait only for server initialization, not for a client. */
    for (int i = 0; i < 500 && s_start_result == SSH_START_PENDING; ++i)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    if (s_start_result != 0)
    {
        printf("ssh: server initialization failed. Check tdsh-ssh log above.\n");
        return 1;
    }

    printf("SSH/SFTP server started on port %u.\n", (unsigned)port);
    printf("wolfSSL/wolfSSH allocations use a private 64 KiB %s heap.\n", ssh_arena_where());
    printf("Login with a tdsh username/password.\n");
    return 0;
}

static int ssh_stop(void)
{
    if (!s_running && s_server_task == NULL)
    {
        printf("SSH server is not running.\n");
        return 0;
    }

    s_running = false;

    int fd = s_listen_fd;
    if (fd >= 0)
    {
        /* The server task owns close(). shutdown() is enough to unblock accept. */
        shutdown(fd, SHUT_RDWR);
    }
    ssh_shutdown_client_fd();

    for (int i = 0; i < 250 && s_server_task != NULL; ++i)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    if (s_server_task != NULL)
    {
        printf("ssh: server shutdown timed out.\n");
        return 1;
    }

    printf("SSH/SFTP server stopped.\n");
    return 0;
}

/* status and control for GUI front ends. */
bool tdsh_ssh_is_running(uint16_t *port, int *clients)
{
    if (port)
        *port = s_port;
    if (clients)
        *clients = client_count_get();
    return s_running;
}

int tdsh_ssh_set_running(bool on)
{
    if (on == s_running)
        return 0;
    return on ? ssh_start(s_port ? s_port : TDSH_SSH_DEFAULT_PORT) : ssh_stop();
}

int tdsh_cmd_ssh(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: ssh <start|stop|restart|status> [port] | ssh hostkey [new]\n");
        return 2;
    }

    if (strcmp(argv[1], "hostkey") == 0)
    {
        if (argc == 2)
        {
            if (s_hostkey_kind)
                printf("Host key: %s\nFingerprint: %s\n", s_hostkey_kind, s_hostkey_fp[0] ? s_hostkey_fp : "?");
            else
                printf("Host key: not loaded yet (the server makes or loads it when it starts)\n");
            return 0;
        }
        if (argc != 3 || strcmp(argv[2], "new") != 0)
        {
            printf("usage: ssh hostkey [new]\n");
            return 2;
        }
        if (strcmp(session->username, "root") != 0)
        {
            printf("ssh: permission denied: root required\n");
            return 1;
        }
        if (!hostkey_erase())
        {
            printf("ssh: could not delete the stored host key\n");
            return 1;
        }
        printf("Host key deleted. The server makes a new one when it next starts%s.\n"
               "SSH and SFTP clients will then warn that the host key changed.\n",
               s_running ? " (ssh restart)" : "");
        return 0;
    }

    if (strcmp(argv[1], "status") == 0)
    {
        printf("SSH/SFTP server: %s\n", s_running ? "running" : "stopped");
        printf("Port: %u\n", (unsigned)s_port);
        if (s_hostkey_kind)
            printf("Host key: %s, %s\n", s_hostkey_kind, s_hostkey_fp);
        printf("Active clients: %d / %d\n", client_count_get(), TDSH_SSH_MAX_CLIENTS);
        printf("wolfSSL allocator: %s%s\n", s_allocators_installed ? "private heap in " : "not initialized",
               s_allocators_installed ? ssh_arena_where() : "");
        printf("Private SSH heap: %u bytes (%s)\n", (unsigned)SSH_PRIVATE_HEAP_SIZE,
               s_ssh_heap_arena ? "allocated" : "allocated on the first start");
        printf("Allocator guard errors: %u\n", (unsigned)s_guard_errors);
        printf("Internal RAM free: %u bytes\n",
               (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT));
        return 0;
    }

    if (strcmp(session->username, "root") != 0 && !tdsh_is_physical_console())
    {
        printf("ssh: permission denied: root, or any user on the local console/desktop\n");
        return 1;
    }

    uint16_t port = s_port ? s_port : TDSH_SSH_DEFAULT_PORT;
    if (argc >= 3)
    {
        char *end = NULL;
        long p = strtol(argv[2], &end, 10);
        if (end == argv[2] || *end != '\0' || p < 1 || p > 65535)
        {
            printf("ssh: invalid port\n");
            return 2;
        }
        port = (uint16_t)p;
    }

    if (strcmp(argv[1], "start") == 0)
        return ssh_start(port);
    if (strcmp(argv[1], "stop") == 0)
        return ssh_stop();
    if (strcmp(argv[1], "restart") == 0)
    {
        if (ssh_stop() != 0)
            return 1;
        vTaskDelay(pdMS_TO_TICKS(100));
        return ssh_start(port);
    }

    printf("usage: ssh <start|stop|restart|status> [port]\n");
    return 2;
}
