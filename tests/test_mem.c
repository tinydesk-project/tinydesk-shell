/*
 * test_mem.c - peek and poke over a port's memory regions (mem_regions).
 *
 * The "port" lists arrays of this program as its regions, so every rule can
 * be checked on a PC: widths, alignment, region ends, read-only regions,
 * overlapping regions, the value-only output for scripts, dumps and root
 * only.
 */
#include <inttypes.h>
#include <stdarg.h>
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

static uint32_t ram[16];                                                 /* 64 bytes, 8/16/32 */
static uint32_t regs[4];                                                 /* 32-bit only */
static const uint32_t rom[4] = {0x11223344u, 0x55667788u, 0x99aabbccu, 0xddeeff00u}; /* read-only */
static uint32_t block[8]; /* read-only, but words 1 and 2 are writable (like GPIO outputs) */

static tdsh_mem_region_t s_regions[5];
static size_t s_region_count;

static const tdsh_mem_region_t *test_regions(void *context, size_t *count)
{
    (void)context;
    *count = s_region_count;
    return s_regions;
}

static const tdsh_platform_api_t s_with_regions = {
    .name = "test-mem",
    .mem_regions = test_regions,
};

static const tdsh_platform_api_t s_without_regions = {
    .name = "test-plain",
};

static void start_core(const tdsh_platform_api_t *platform)
{
    tdsh_core_config_t cfg = TDSH_CORE_CONFIG_DEFAULT();
    cfg.platform = platform;
    tdsh_core_reset();
    CHECK(tdsh_core_init(&cfg) == 0, "core starts");
    CHECK(tdsh_register_core_builtins() == 0, "core commands register");
}

static int run(tdsh_session_t *s, const char *fmt, ...)
{
    char line[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);
    return tdsh_execute_line(s, line);
}

/* What a script gets from OUT=$(command). */
static const char *output_of(tdsh_session_t *s, const char *command)
{
    char line[256];
    tdsh_var_unset(s, "OUT");
    snprintf(line, sizeof(line), "OUT=$(%s)", command);
    tdsh_execute_line(s, line);
    const char *v = tdsh_var_get(s, "OUT");
    return v ? v : "";
}

/* Exactly what a command prints, line breaks included, read back from a file
 * (longer than a shell variable holds). */
static const char *printed(tdsh_session_t *s, const char *command)
{
    static char buf[1024];
    buf[0] = '\0';
    FILE *f = fopen("test_mem_out.txt", "w+");
    if (!f)
        return buf;
    FILE *old = stdout;
    stdout = f;
    tdsh_execute_line(s, command);
    fflush(stdout);
    stdout = old;
    rewind(f);
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    fclose(f);
    remove("test_mem_out.txt");
    return buf;
}

static char *addr(const void *p, size_t offset)
{
    static char buf[4][32];
    static int next;
    char *out = buf[next++ % 4];
    snprintf(out, sizeof(buf[0]), "0x%" PRIxPTR, (uintptr_t)p + offset);
    return out;
}

int main(void)
{
    tdsh_session_t root;
    tdsh_session_t user;

    /* Without the hook, or with an empty table, neither command exists. */
    start_core(&s_without_regions);
    CHECK(tdsh_command_find("peek") == NULL && tdsh_command_find("poke") == NULL, "no hook: no commands");
    s_region_count = 0;
    start_core(&s_with_regions);
    CHECK(tdsh_command_find("peek") == NULL && tdsh_command_find("poke") == NULL, "empty table: no commands");

    for (unsigned i = 0; i < sizeof(ram); ++i)
        ((unsigned char *)ram)[i] = (unsigned char)i;
    s_regions[0] = (tdsh_mem_region_t){"ram", (uintptr_t)ram, sizeof(ram), TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32};
    s_regions[1] = (tdsh_mem_region_t){"regs", (uintptr_t)regs, sizeof(regs), TDSH_MEM_32};
    s_regions[2] = (tdsh_mem_region_t){"rom", (uintptr_t)rom, sizeof(rom),
                                       TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32 | TDSH_MEM_READONLY};
    s_regions[3] = (tdsh_mem_region_t){"block", (uintptr_t)block, sizeof(block), TDSH_MEM_32 | TDSH_MEM_READONLY};
    s_regions[4] = (tdsh_mem_region_t){"out", (uintptr_t)block + 4, 8, TDSH_MEM_32};
    s_region_count = 5;
    start_core(&s_with_regions);
    CHECK(tdsh_command_find("peek") != NULL && tdsh_command_find("poke") != NULL, "regions: both commands");
    CHECK(tdsh_session_init(&root, "root", false) == 0, "root session");
    CHECK(tdsh_session_init(&user, "alice", false) == 0, "user session");

    tdsh_memory_stats_t before;
    tdsh_memory_get_stats(&before);

    /* Root only. */
    CHECK(run(&user, "peek %s", addr(ram, 0)) == 126, "peek refused for a user");
    CHECK(run(&user, "poke %s 1", addr(ram, 0)) == 126, "poke refused for a user");
    CHECK(run(&user, "peek -l") == 126, "peek -l refused for a user");

    /* One value: just the value, 32-bit by default, digits by width. */
    char want[64];
    uint32_t w32;
    uint16_t w16;
    memcpy(&w32, (unsigned char *)ram + 4, 4);
    snprintf(want, sizeof(want), "0x%08" PRIx32, w32);
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "peek %s", addr(ram, 4));
    CHECK(strcmp(output_of(&root, cmd), want) == 0, "peek: 32-bit value");
    snprintf(cmd, sizeof(cmd), "peek %" PRIuPTR, (uintptr_t)ram + 4);
    CHECK(strcmp(output_of(&root, cmd), want) == 0, "peek: a decimal address");
    snprintf(cmd, sizeof(cmd), "peek -w 8 %s", addr(ram, 1));
    CHECK(strcmp(output_of(&root, cmd), "0x01") == 0, "peek -w 8");
    memcpy(&w16, (unsigned char *)ram + 2, 2);
    snprintf(want, sizeof(want), "0x%04x", (unsigned)w16);
    snprintf(cmd, sizeof(cmd), "peek -w 16 %s", addr(ram, 2));
    CHECK(strcmp(output_of(&root, cmd), want) == 0, "peek -w 16");
    snprintf(cmd, sizeof(cmd), "peek %s", addr(rom, 8));
    CHECK(strcmp(output_of(&root, cmd), "0x99aabbcc") == 0, "peek a read-only region");
    CHECK(run(&root, "peek %s", addr(ram, 4)) == 0, "peek: status 0");

    /* Refusals: exit status 1. */
    CHECK(run(&root, "peek %s", addr(ram, 2)) == 1, "misaligned 32-bit");
    CHECK(run(&root, "peek -w 16 %s", addr(ram, 1)) == 1, "misaligned 16-bit");
    CHECK(run(&root, "peek %s 2", addr(ram, 60)) == 1, "a dump past the region's end");
    CHECK(run(&root, "peek %s 1", addr(ram, 60)) == 0, "the region's last word");
    CHECK(run(&root, "peek 0x10") == 1, "an address in no region");
    CHECK(run(&root, "peek -w 8 %s", addr(regs, 0)) == 1, "a width the region does not allow");
    CHECK(run(&root, "peek %s", addr(regs, 12)) == 0, "the width it allows");
    CHECK(run(&root, "poke %s 1", addr(rom, 0)) == 1 && rom[0] == 0x11223344u, "poke a read-only region");

    /* Usage errors: exit status 2. */
    CHECK(run(&root, "peek") == 2, "peek alone");
    CHECK(run(&root, "peek -w 12 %s", addr(ram, 0)) == 2, "an unknown width");
    CHECK(run(&root, "peek -w") == 2, "-w without a width");
    CHECK(run(&root, "peek 0x") == 2, "0x without digits");
    CHECK(run(&root, "peek 0x1g") == 2, "not a number");
    CHECK(run(&root, "peek %s 0", addr(ram, 0)) == 2, "a count of 0");
    CHECK(run(&root, "peek %s 1 2", addr(ram, 0)) == 2, "too many operands");
    CHECK(run(&root, "peek -l x") == 2, "peek -l with an operand");
    CHECK(run(&root, "poke %s", addr(ram, 0)) == 2, "poke without a value");
    CHECK(run(&root, "poke %s -1", addr(ram, 0)) == 2, "a negative value");

    /* poke at each width. */
    CHECK(run(&root, "poke %s 0xdeadbeef", addr(ram, 8)) == 0 && ram[2] == 0xdeadbeefu, "poke 32-bit");
    CHECK(run(&root, "poke -w 8 %s 0xab", addr(ram, 12)) == 0 && ((unsigned char *)ram)[12] == 0xab, "poke -w 8");
    CHECK(run(&root, "poke -w 8 %s 0x1ff", addr(ram, 12)) == 1 && ((unsigned char *)ram)[12] == 0xab,
          "a value too wide for 8 bits");
    CHECK(run(&root, "poke -w 16 %s 4660", addr(ram, 14)) == 0, "poke -w 16, decimal value");
    memcpy(&w16, (unsigned char *)ram + 14, 2);
    CHECK(w16 == 0x1234, "poke -w 16 wrote 0x1234");
    CHECK(run(&root, "poke -w 16 %s 0x10000", addr(ram, 14)) == 1, "a value too wide for 16 bits");
    CHECK(run(&root, "poke %s 0x100000000", addr(ram, 8)) == 1 && ram[2] == 0xdeadbeefu, "a value too wide for 32 bits");
    CHECK(run(&root, "poke %s 7", addr(regs, 4)) == 0 && regs[1] == 7, "poke a 32-bit-only region");
    CHECK(run(&root, "poke -w 16 %s 7", addr(regs, 4)) == 1, "poke -w 16 in a 32-bit-only region");

    /* Overlapping regions: an access is allowed when one region allows all
     * of it, whatever the order of the table. */
    CHECK(run(&root, "poke %s 5", addr(block, 4)) == 0 && block[1] == 5, "poke the writable window");
    CHECK(run(&root, "poke %s 6", addr(block, 8)) == 0 && block[2] == 6, "the window's last word");
    CHECK(run(&root, "poke %s 7", addr(block, 0)) == 1 && block[0] == 0, "the read-only block around it");
    CHECK(run(&root, "poke %s 7", addr(block, 12)) == 1 && block[3] == 0, "past the window");
    CHECK(run(&root, "peek %s 8", addr(block, 0)) == 0, "a dump of the whole block");
    CHECK(run(&root, "peek %s 3", addr(block, 4)) == 0, "a dump from the window past its end");
    CHECK(strstr(printed(&root, "peek -l"), "out") != NULL, "peek -l lists the window");
    snprintf(cmd, sizeof(cmd), "poke %s 7", addr(block, 0));
    CHECK(strstr(printed(&root, cmd), "block is read-only") != NULL, "the refusal names the region");

    /* Dumps: 16 bytes per line, each line starts with its address. */
    char expect[256];
    int len = snprintf(expect, sizeof(expect), "0x%08" PRIxPTR ":", (uintptr_t)ram);
    for (int i = 0; i < 20; ++i)
    {
        if (i == 16)
            len += snprintf(expect + len, sizeof(expect) - len, "\n0x%08" PRIxPTR ":", (uintptr_t)ram + 16);
        len += snprintf(expect + len, sizeof(expect) - len, " %02x", ((unsigned char *)ram)[i]);
    }
    snprintf(expect + len, sizeof(expect) - len, "\n");
    snprintf(cmd, sizeof(cmd), "peek -w 8 %s 20", addr(ram, 0));
    CHECK(strcmp(printed(&root, cmd), expect) == 0, "dump: 16 bytes per line, each line with its address");
    snprintf(expect, sizeof(expect), "0x%08" PRIxPTR ": 11223344 55667788 99aabbcc ddeeff00\n", (uintptr_t)rom);
    snprintf(cmd, sizeof(cmd), "peek %s 4", addr(rom, 0));
    CHECK(strcmp(printed(&root, cmd), expect) == 0, "dump: four words on one line");
    CHECK(run(&root, "peek %s 5", addr(rom, 0)) == 1, "a dump of 5 words crosses rom's 16 bytes");

    /* The list. */
    const char *list = printed(&root, "peek -l");
    CHECK(strstr(list, "REGION") && strstr(list, "ram") && strstr(list, "regs") && strstr(list, "rom"),
          "peek -l names every region");
    CHECK(strstr(list, "8 16 32") && strstr(list, "read/write"), "peek -l shows widths and access");
    snprintf(want, sizeof(want), "0x%08" PRIxPTR, (uintptr_t)rom + sizeof(rom) - 1);
    CHECK(strstr(list, want) != NULL, "peek -l shows each region's last address");

    /* In a script: V=$(peek ...) and a test on it. */
    snprintf(cmd, sizeof(cmd), "V=$(peek %s)", addr(rom, 4));
    run(&root, "%s", cmd);
    CHECK(run(&root, "test $V = 0x55667788") == 0, "a script can test a peeked value");

    tdsh_memory_stats_t after;
    tdsh_memory_get_stats(&after);
    CHECK(after.live_blocks == before.live_blocks, "no shell memory left allocated");

    if (failures)
        printf("%d failure(s)\n", failures);
    else
        printf("peek/poke tests passed\n");
    return failures ? 1 : 0;
}
