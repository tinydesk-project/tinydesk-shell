/*
 * test_script_oom.c - a script that runs out of memory while it is loaded
 * says so instead of returning silently (tinydesk-shell #2).
 *
 * The "port" refuses reallocations above a limit, so the line table of a
 * 100-line script cannot grow past its first 64 lines.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdsh.h"

static int failures;

#define CHECK(cond, what)                                         \
    do                                                            \
    {                                                             \
        if (!(cond))                                              \
        {                                                         \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, what); \
            failures++;                                           \
        }                                                         \
    } while (0)

static size_t s_realloc_limit = (size_t)-1;

static void *test_malloc(void *context, size_t size)
{
    (void)context;
    return malloc(size);
}

static void *test_calloc(void *context, size_t count, size_t size)
{
    (void)context;
    return calloc(count, size);
}

static void *test_realloc(void *context, void *ptr, size_t size)
{
    (void)context;
    return size > s_realloc_limit ? NULL : realloc(ptr, size);
}

static void test_free(void *context, void *ptr)
{
    (void)context;
    free(ptr);
}

static const tdsh_platform_api_t s_platform = {
    .name = "test-oom",
    .malloc_fn = test_malloc,
    .calloc_fn = test_calloc,
    .realloc_fn = test_realloc,
    .free_fn = test_free,
};

/* What running the script prints, read back from a file. */
static const char *printed_run(tdsh_session_t *s, const char *path, int *status)
{
    static char buf[2048];
    buf[0] = '\0';
    FILE *f = fopen("test_script_oom_out.txt", "w+");
    if (!f)
        return buf;
    FILE *old = stdout;
    stdout = f;
    *status = tdsh_run_script_in_session(s, path);
    fflush(stdout);
    stdout = old;
    rewind(f);
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    fclose(f);
    remove("test_script_oom_out.txt");
    return buf;
}

int main(void)
{
    FILE *f = fopen("oom.tdsh", "w");
    CHECK(f != NULL, "script written");
    if (!f)
        return 1;
    for (int i = 0; i < 100; ++i)
        fprintf(f, "X=%d\n", i);
    fclose(f);

    tdsh_core_config_t cfg = TDSH_CORE_CONFIG_DEFAULT();
    cfg.platform = &s_platform;
    tdsh_core_reset();
    CHECK(tdsh_core_init(&cfg) == 0, "core starts");
    CHECK(tdsh_register_core_builtins() == 0, "core commands register");
    tdsh_session_t root;
    CHECK(tdsh_session_init(&root, "root", false) == 0, "root session");
    tdsh_memory_stats_t before;
    tdsh_memory_get_stats(&before);

    /* Enough memory: the script runs to its last line. */
    int status = -1;
    printed_run(&root, "/oom.tdsh", &status);
    const char *x = tdsh_var_get(&root, "X");
    CHECK(status == 0 && x && strcmp(x, "99") == 0, "the script runs with enough memory");

    /* The line table cannot grow past 64 lines: a message names the line,
     * the status is 2 and no line of the script runs. */
    tdsh_var_unset(&root, "X");
    s_realloc_limit = 64 * 24; /* 64 line entries (16 bytes each) fit, 128 do not */
    const char *out = printed_run(&root, "/oom.tdsh", &status);
    CHECK(status == 2, "status 2");
    CHECK(strstr(out, "not enough memory to load the script") != NULL, "says it ran out of memory");
    CHECK(strstr(out, "/oom.tdsh:65:") != NULL, "names the line it stopped at");
    CHECK(tdsh_var_get(&root, "X") == NULL, "nothing of the script ran");
    s_realloc_limit = (size_t)-1;

    tdsh_memory_stats_t after;
    tdsh_memory_get_stats(&after);
    CHECK(after.live_blocks == before.live_blocks, "no shell memory left allocated");

    remove("oom.tdsh");
    if (failures)
        printf("%d failure(s)\n", failures);
    else
        printf("script out-of-memory tests passed\n");
    return failures ? 1 : 0;
}
