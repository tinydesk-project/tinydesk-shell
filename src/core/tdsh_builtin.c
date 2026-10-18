#include "tdsh.h"

#include <dirent.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define C_RESET "\033[0m"
#define C_BLUE  "\033[1;34m"
#define C_CYAN  "\033[1;36m"
#define C_RED   "\033[1;31m"

static int cmd_help(tdsh_session_t *session, int argc, char **argv);
static int cmd_clear(tdsh_session_t *session, int argc, char **argv);
static int cmd_pwd(tdsh_session_t *session, int argc, char **argv);
static int cmd_cd(tdsh_session_t *session, int argc, char **argv);
static int cmd_ls(tdsh_session_t *session, int argc, char **argv);
static int cmd_mkdir(tdsh_session_t *session, int argc, char **argv);
static int cmd_touch(tdsh_session_t *session, int argc, char **argv);
static int cmd_cat(tdsh_session_t *session, int argc, char **argv);
static int cmd_head(tdsh_session_t *session, int argc, char **argv);
static int cmd_rm(tdsh_session_t *session, int argc, char **argv);
static int cmd_mv(tdsh_session_t *session, int argc, char **argv);
static int cmd_cp(tdsh_session_t *session, int argc, char **argv);
static int cmd_echo(tdsh_session_t *session, int argc, char **argv);
static int cmd_test(tdsh_session_t *session, int argc, char **argv);
static int cmd_sleep(tdsh_session_t *session, int argc, char **argv);
static int cmd_platform(tdsh_session_t *session, int argc, char **argv);
static int cmd_whoami(tdsh_session_t *session, int argc, char **argv);
static int cmd_free(tdsh_session_t *session, int argc, char **argv);
static int cmd_uptime(tdsh_session_t *session, int argc, char **argv);
static int cmd_set(tdsh_session_t *session, int argc, char **argv);
static int cmd_unset(tdsh_session_t *session, int argc, char **argv);
static int cmd_tdsh(tdsh_session_t *session, int argc, char **argv);
static int cmd_version(tdsh_session_t *session, int argc, char **argv);
static int cmd_peek(tdsh_session_t *session, int argc, char **argv);
static int cmd_poke(tdsh_session_t *session, int argc, char **argv);

static const tdsh_command_t s_core_commands[] = {
    {"help", "help [command]", "Show commands or command help", cmd_help, 0},
    {"sleep", "sleep <seconds>", "Sleep for a floating-point number of seconds", cmd_sleep, 0},
    {"pwd", "pwd", "Print current working directory", cmd_pwd, 0},
    {"cd", "cd [directory]", "Change directory", cmd_cd, 0},
    {"cp", "cp <source ...> <destination>", "Copy files or directory trees", cmd_cp, 0},
    {"head", "head <file ...> [-l lines]", "Print first lines of files", cmd_head, 0},
    {"cat", "cat <file ...>", "Print entire files", cmd_cat, 0},
    {"touch", "touch <file ...>", "Create files if they do not exist", cmd_touch, 0},
    {"mv", "mv <source ...> <destination>", "Move or rename files/directories", cmd_mv, 0},
    {"rm", "rm [-r] [-y] <path ...>", "Remove files or directory trees", cmd_rm, 0},
    {"mkdir", "mkdir [-p] <directory ...>", "Create directories", cmd_mkdir, 0},
    {"clear", "clear", "Clear the terminal", cmd_clear, 0},
    {"ls", "ls [-a] [-l] [path ...]", "List directory contents", cmd_ls, 0},
    {"echo", "echo [text ...]", "Print text (generic shell redirection is supported)", cmd_echo, 0},
    {"test", "test EXPRESSION", "Evaluate file, string or integer conditions", cmd_test, 0},
    {"[", "[ EXPRESSION ]", "Bracket form of test", cmd_test, 0},
    {"tdsh", "tdsh run <file.tdsh|directory> [--bg]", "Run .tdsh shell scripts", cmd_tdsh, TDSH_CMD_BG_ALLOWED},
    {"whoami", "whoami", "Print current user", cmd_whoami, 0},
    {"platform", "platform", "Show the active platform port", cmd_platform, 0},
    {"free", "free", "Show shell core allocation statistics", cmd_free, 0},
    {"uptime", "uptime", "Show monotonic platform uptime", cmd_uptime, 0},
    {"set", "set", "Show shell variables", cmd_set, 0},
    {"unset", "unset <name ...>", "Remove shell variables", cmd_unset, 0},
    {"version", "version", "Show the TinyDesk Shell version", cmd_version, 0},
};

/* Only when the port lists memory regions (tdsh_platform_api_t mem_regions). */
static const tdsh_command_t s_mem_commands[] = {
    {"peek", "peek -l | peek [-w 8|16|32] <address> [count]", "Read memory the port allows", cmd_peek, TDSH_CMD_ROOT_ONLY},
    {"poke", "poke [-w 8|16|32] <address> <value>", "Write memory the port allows", cmd_poke, TDSH_CMD_ROOT_ONLY},
};

static const tdsh_mem_region_t *mem_regions(size_t *count)
{
    const tdsh_core_config_t *cfg = tdsh_core_config();
    const tdsh_platform_api_t *p = cfg ? cfg->platform : NULL;
    const tdsh_mem_region_t *regions = NULL;
    *count = 0;
    if (p && p->mem_regions)
        regions = p->mem_regions(p->context, count);
    if (!regions)
        *count = 0;
    return regions;
}

int tdsh_register_core_builtins(void)
{
    int rc = tdsh_register_commands(s_core_commands,
                                    sizeof(s_core_commands) / sizeof(s_core_commands[0]));
    size_t regions = 0;
    if (rc == 0 && mem_regions(&regions) && regions > 0)
    {
        rc = tdsh_register_commands(s_mem_commands,
                                    sizeof(s_mem_commands) / sizeof(s_mem_commands[0]));
    }
    return rc;
}

static int usage(const tdsh_command_t *cmd)
{
    if (cmd)
        printf("usage: %s\n", cmd->usage);
    return 2;
}

static int path_error(const char *operation, const char *path)
{
    printf("tdsh: %s '%s': %s\n", operation, path, strerror(errno));
    return 1;
}

static const char *base_name(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

static int join_real(const char *dir, const char *name, char *out, size_t out_size)
{
    int written = snprintf(out, out_size, "%s/%s", dir, name);
    return (written < 0 || (size_t)written >= out_size) ? -ENAMETOOLONG : 0;
}

static bool real_is_dir(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

static int remove_real_recursive(const char *path)
{
    struct stat st;
    if (stat(path, &st) != 0)
        return -errno;

    if (!S_ISDIR(st.st_mode))
    {
        return unlink(path) == 0 ? 0 : -errno;
    }

    DIR *dir = opendir(path);
    if (!dir)
        return -errno;

    const size_t child_cap = TDSH_MAX_REAL_PATH;
    char *child = tdsh_malloc(child_cap);
    if (child == NULL)
    {
        closedir(dir);
        return -ENOMEM;
    }

    struct dirent *entry;
    int rc = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (join_real(path, entry->d_name, child, child_cap) != 0)
        {
            rc = -ENAMETOOLONG;
            break;
        }
        rc = remove_real_recursive(child);
        if (rc != 0)
            break;
    }
    tdsh_free(child);
    closedir(dir);
    if (rc != 0)
        return rc;
    return rmdir(path) == 0 ? 0 : -errno;
}

static int copy_file_real(const char *src, const char *dst)
{
    FILE *in = fopen(src, "rb");
    if (!in)
        return -errno;

    FILE *out = fopen(dst, "wb");
    if (!out)
    {
        int rc = -errno;
        fclose(in);
        return rc;
    }

    uint8_t *buffer = tdsh_malloc(TDSH_COPY_BUFFER_SIZE);
    if (buffer == NULL)
    {
        fclose(out);
        fclose(in);
        return -ENOMEM;
    }

    int rc = 0;
    for (;;)
    {
        size_t n = fread(buffer, 1, TDSH_COPY_BUFFER_SIZE, in);
        if (n > 0 && fwrite(buffer, 1, n, out) != n)
        {
            rc = -EIO;
            break;
        }
        if (n < TDSH_COPY_BUFFER_SIZE)
        {
            if (ferror(in))
                rc = -EIO;
            break;
        }
    }

    tdsh_free(buffer);
    fclose(out);
    fclose(in);
    return rc;
}

static int copy_real_recursive(const char *src, const char *dst)
{
    struct stat st;
    if (stat(src, &st) != 0)
        return -errno;

    if (!S_ISDIR(st.st_mode))
        return copy_file_real(src, dst);

    if (mkdir(dst, 0755) != 0 && errno != EEXIST)
        return -errno;

    DIR *dir = opendir(src);
    if (!dir)
        return -errno;

    const size_t child_cap = TDSH_MAX_REAL_PATH;
    char *children = tdsh_malloc(child_cap * 2U);
    if (children == NULL)
    {
        closedir(dir);
        return -ENOMEM;
    }
    char *src_child = children;
    char *dst_child = children + child_cap;

    int rc = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (join_real(src, entry->d_name, src_child, child_cap) != 0 ||
            join_real(dst, entry->d_name, dst_child, child_cap) != 0)
        {
            rc = -ENAMETOOLONG;
            break;
        }
        rc = copy_real_recursive(src_child, dst_child);
        if (rc != 0)
            break;
    }
    tdsh_free(children);
    closedir(dir);
    return rc;
}

static int cmd_help(tdsh_session_t *session, int argc, char **argv)
{
    if (argc > 2)
        return usage(tdsh_command_find("help"));
    if (argc == 2)
    {
        const tdsh_command_t *cmd = tdsh_command_find(argv[1]);
        if (!cmd)
        {
            printf("help: no such command: %s\n", argv[1]);
            return 1;
        }
        printf("%-12s %s\nusage: %s\n", cmd->name, cmd->help, cmd->usage);
        return 0;
    }

    size_t count = 0;
    const tdsh_command_t *commands = tdsh_commands_get(&count);
    printf("TinyDesk Shell %s commands:\n\n", TDSH_VERSION);
    for (size_t i = 0; i < count; ++i)
    {
        if ((session->terminal_caps & TDSH_TERM_CAP_COLOR) != 0)
            printf("  " C_CYAN "%-10s" C_RESET " %s\n", commands[i].name, commands[i].help);
        else
            printf("  %-10s %s\n", commands[i].name, commands[i].help);
    }
    return 0;
}

static int cmd_clear(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("clear"));
    printf("\033[2J\033[H");
    return 0;
}

static int cmd_pwd(tdsh_session_t *session, int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("pwd"));
    printf("%s\n", session->cwd);
    return 0;
}

static int cmd_cd(tdsh_session_t *session, int argc, char **argv)
{
    if (argc > 2)
        return usage(tdsh_command_find("cd"));
    const char *target = argc == 1 ? session->home : argv[1];

    char real[TDSH_MAX_REAL_PATH];
    char logical[TDSH_MAX_PATH];
    int rc = tdsh_path_to_real(session, target, real, sizeof(real), logical, sizeof(logical));
    if (rc != 0)
    {
        printf("cd: invalid path\n");
        return 1;
    }

    struct stat st;
    if (stat(real, &st) != 0)
        return path_error("cd", target);
    if (!S_ISDIR(st.st_mode))
    {
        printf("cd: '%s' is not a directory\n", target);
        return 1;
    }

    snprintf(session->cwd, sizeof(session->cwd), "%s", logical);
    return 0;
}

static int list_one(tdsh_session_t *session, const char *arg, bool show_all, bool long_mode)
{
    char real[TDSH_MAX_REAL_PATH];
    char logical[TDSH_MAX_PATH];
    if (tdsh_path_to_real(session, arg, real, sizeof(real), logical, sizeof(logical)) != 0)
    {
        printf("ls: invalid path: %s\n", arg);
        return 1;
    }

    struct stat st;
    if (stat(real, &st) != 0)
        return path_error("ls", arg);

    if (!S_ISDIR(st.st_mode))
    {
        if (long_mode)
            printf("%8ld  %s\n", (long)st.st_size, base_name(logical));
        else
            printf("%s\n", base_name(logical));
        return 0;
    }

    DIR *dir = opendir(real);
    if (!dir)
        return path_error("ls", arg);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!show_all && entry->d_name[0] == '.')
            continue;
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char child[TDSH_MAX_REAL_PATH + 64];
        struct stat child_st;
        bool is_dir = false;
        if (join_real(real, entry->d_name, child, sizeof(child)) == 0 && stat(child, &child_st) == 0)
        {
            is_dir = S_ISDIR(child_st.st_mode);
        }
        else
        {
            memset(&child_st, 0, sizeof(child_st));
        }

        if (long_mode)
        {
            printf("%c %8ld  ", is_dir ? 'd' : '-', (long)child_st.st_size);
        }
        if (is_dir && (session->terminal_caps & TDSH_TERM_CAP_COLOR) != 0)
            printf(C_BLUE "%s" C_RESET "  ", entry->d_name);
        else
            printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
    return 0;
}

static int cmd_ls(tdsh_session_t *session, int argc, char **argv)
{
    bool show_all = false;
    bool long_mode = false;
    int paths = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-a") == 0)
            show_all = true;
        else if (strcmp(argv[i], "-l") == 0)
            long_mode = true;
        else
            paths++;
    }

    if (paths == 0)
        return list_one(session, session->cwd, show_all, long_mode);

    int rc = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-' && (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-l") == 0))
            continue;
        if (paths > 1)
            printf("%s:\n", argv[i]);
        if (list_one(session, argv[i], show_all, long_mode) != 0)
            rc = 1;
    }
    return rc;
}

static int mkdir_parents(const char *real)
{
    char tmp[TDSH_MAX_REAL_PATH];
    if (snprintf(tmp, sizeof(tmp), "%s", real) >= (int)sizeof(tmp))
        return -ENAMETOOLONG;

    for (char *p = tmp + strlen(TDSH_MOUNT_POINT) + 1; *p; ++p)
    {
        if (*p == '/')
        {
            *p = '\0';
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST)
                return -errno;
            *p = '/';
        }
    }
    if (mkdir(tmp, 0755) != 0 && errno != EEXIST)
        return -errno;
    return 0;
}

static int cmd_mkdir(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("mkdir"));
    bool parents = false;
    int rc_all = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            parents = true;
            continue;
        }
        char real[TDSH_MAX_REAL_PATH];
        if (tdsh_path_to_real(session, argv[i], real, sizeof(real), NULL, 0) != 0)
        {
            printf("mkdir: invalid path: %s\n", argv[i]);
            rc_all = 1;
            continue;
        }
        int rc = parents ? mkdir_parents(real) : ((mkdir(real, 0755) == 0) ? 0 : -errno);
        if (rc != 0)
        {
            errno = -rc;
            path_error("mkdir", argv[i]);
            rc_all = 1;
        }
    }
    return rc_all;
}

static int cmd_touch(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("touch"));
    int rc = 0;
    for (int i = 1; i < argc; ++i)
    {
        char real[TDSH_MAX_REAL_PATH];
        if (tdsh_path_to_real(session, argv[i], real, sizeof(real), NULL, 0) != 0)
        {
            rc = 1;
            continue;
        }
        FILE *f = fopen(real, "ab");
        if (!f)
        {
            path_error("touch", argv[i]);
            rc = 1;
            continue;
        }
        fclose(f);
    }
    return rc;
}

static int print_file(tdsh_session_t *session, const char *path, long max_lines)
{
    char real[TDSH_MAX_REAL_PATH];
    if (tdsh_path_to_real(session, path, real, sizeof(real), NULL, 0) != 0)
        return 1;
    FILE *f = fopen(real, "r");
    if (!f)
        return path_error("open", path);

    char buf[256];
    long lines = 0;
    while (lines < max_lines && fgets(buf, sizeof(buf), f) != NULL)
    {
        fputs(buf, stdout);
        if (strchr(buf, '\n'))
            lines++;
    }
    fclose(f);
    return 0;
}

static int cmd_cat(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("cat"));
    int rc = 0;
    for (int i = 1; i < argc; ++i)
        if (print_file(session, argv[i], 0x7fffffffL) != 0)
            rc = 1;
    return rc;
}

static int cmd_head(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("head"));
    long lines = 10;
    int rc = 0;

    for (int i = 1; i < argc; ++i)
    {
        if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-n") == 0) && i + 1 < argc)
        {
            char *end = NULL;
            lines = strtol(argv[++i], &end, 10);
            if (!end || *end || lines < 0)
                return usage(tdsh_command_find("head"));
        }
    }

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-n") == 0)
        {
            i++;
            continue;
        }
        if (print_file(session, argv[i], lines) != 0)
            rc = 1;
    }
    return rc;
}

static int cmd_rm(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("rm"));
    int rc_all = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-y") == 0)
            continue;
        char real[TDSH_MAX_REAL_PATH];
        char logical[TDSH_MAX_PATH];
        if (tdsh_path_to_real(session, argv[i], real, sizeof(real), logical, sizeof(logical)) != 0)
        {
            rc_all = 1;
            continue;
        }
        if (strcmp(logical, "/") == 0)
        {
            printf("rm: refusing to remove filesystem root\n");
            rc_all = 1;
            continue;
        }
        int rc = remove_real_recursive(real);
        if (rc != 0)
        {
            errno = -rc;
            path_error("rm", argv[i]);
            rc_all = 1;
        }
    }
    return rc_all;
}

static int resolve_target_real(tdsh_session_t *session, const char *source_arg, const char *dest_arg,
                               bool force_child, char *src_real, size_t src_size,
                               char *dst_real, size_t dst_size)
{
    char src_logical[TDSH_MAX_PATH];
    char dest_real_base[TDSH_MAX_REAL_PATH];
    if (tdsh_path_to_real(session, source_arg, src_real, src_size, src_logical, sizeof(src_logical)) != 0)
        return -EINVAL;
    if (tdsh_path_to_real(session, dest_arg, dest_real_base, sizeof(dest_real_base), NULL, 0) != 0)
        return -EINVAL;

    if (force_child || real_is_dir(dest_real_base))
    {
        return join_real(dest_real_base, base_name(src_logical), dst_real, dst_size);
    }
    if (snprintf(dst_real, dst_size, "%s", dest_real_base) >= (int)dst_size)
        return -ENAMETOOLONG;
    return 0;
}

static int cmd_cp(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 3)
        return usage(tdsh_command_find("cp"));
    bool multiple = argc > 3;
    if (multiple)
    {
        char dest[TDSH_MAX_REAL_PATH];
        if (tdsh_path_to_real(session, argv[argc - 1], dest, sizeof(dest), NULL, 0) != 0 || !real_is_dir(dest))
        {
            printf("cp: destination must be a directory when copying multiple sources\n");
            return 1;
        }
    }

    int rc_all = 0;
    for (int i = 1; i < argc - 1; ++i)
    {
        char src[TDSH_MAX_REAL_PATH];
        char dst[TDSH_MAX_REAL_PATH + 64];
        int rc = resolve_target_real(session, argv[i], argv[argc - 1], multiple, src, sizeof(src), dst, sizeof(dst));
        if (rc == 0)
            rc = copy_real_recursive(src, dst);
        if (rc != 0)
        {
            errno = -rc;
            path_error("cp", argv[i]);
            rc_all = 1;
        }
    }
    return rc_all;
}

static int cmd_mv(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 3)
        return usage(tdsh_command_find("mv"));
    bool multiple = argc > 3;
    if (multiple)
    {
        char dest[TDSH_MAX_REAL_PATH];
        if (tdsh_path_to_real(session, argv[argc - 1], dest, sizeof(dest), NULL, 0) != 0 || !real_is_dir(dest))
        {
            printf("mv: destination must be a directory when moving multiple sources\n");
            return 1;
        }
    }

    int rc_all = 0;
    for (int i = 1; i < argc - 1; ++i)
    {
        char src[TDSH_MAX_REAL_PATH];
        char dst[TDSH_MAX_REAL_PATH + 64];
        int rc = resolve_target_real(session, argv[i], argv[argc - 1], multiple, src, sizeof(src), dst, sizeof(dst));
        if (rc == 0 && rename(src, dst) != 0)
        {
            int rename_errno = errno;
            if (rename_errno == EXDEV)
            {
                /* Cross-VFS move (e.g. LittleFS <-> SMB): copy, then remove source. */
                rc = copy_real_recursive(src, dst);
                if (rc == 0)
                    rc = remove_real_recursive(src);
            }
            else
            {
                rc = -rename_errno;
            }
        }
        if (rc != 0)
        {
            errno = -rc;
            path_error("mv", argv[i]);
            rc_all = 1;
        }
    }
    return rc_all;
}

static int cmd_echo(tdsh_session_t *session, int argc, char **argv)
{
    int redirect = -1;
    bool append = false;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0)
        {
            redirect = i;
            append = argv[i][1] == '>';
            break;
        }
    }

    FILE *out = stdout;
    if (redirect >= 0)
    {
        if (redirect + 1 != argc - 1)
            return usage(tdsh_command_find("echo"));
        char real[TDSH_MAX_REAL_PATH];
        if (tdsh_path_to_real(session, argv[argc - 1], real, sizeof(real), NULL, 0) != 0)
            return 1;
        out = fopen(real, append ? "a" : "w");
        if (!out)
            return path_error("echo", argv[argc - 1]);
    }

    int end = redirect >= 0 ? redirect : argc;
    for (int i = 1; i < end; ++i)
    {
        if (i > 1)
            fputc(' ', out);
        fputs(argv[i], out);
    }
    fputc('\n', out);
    if (out != stdout)
        fclose(out);
    return 0;
}


static bool test_parse_integer(const char *text, long long *value)
{
    if (!text || !*text || !value)
        return false;
    char *end = NULL;
    errno = 0;
    long long v = strtoll(text, &end, 0);
    if (errno != 0 || end == text || *end != '\0')
        return false;
    *value = v;
    return true;
}

static bool test_path_predicate(tdsh_session_t *session,
                                const char *op,
                                const char *path)
{
    char real[TDSH_MAX_REAL_PATH];
    if (tdsh_path_to_real(session, path, real, sizeof(real), NULL, 0) != 0)
    {
        return false;
    }

    struct stat st;
    if (stat(real, &st) != 0)
        return false;

    if (strcmp(op, "-e") == 0)
        return true;
    if (strcmp(op, "-f") == 0)
        return S_ISREG(st.st_mode);
    if (strcmp(op, "-d") == 0)
        return S_ISDIR(st.st_mode);
    if (strcmp(op, "-s") == 0)
        return st.st_size > 0;
    return false;
}

static int cmd_test(tdsh_session_t *session, int argc, char **argv)
{
    bool bracket = argc > 0 && strcmp(argv[0], "[") == 0;

    if (bracket)
    {
        if (argc < 2 || strcmp(argv[argc - 1], "]") != 0)
        {
            printf("[: missing closing ]\n");
            return 2;
        }
        argc--; /* ignore closing ] */
    }

    int pos = 1;
    bool negate = false;

    if (pos < argc && strcmp(argv[pos], "!") == 0)
    {
        negate = true;
        pos++;
    }

    int remaining = argc - pos;
    bool result = false;
    bool valid = true;

    if (remaining == 0)
    {
        result = false;
    }
    else if (remaining == 1)
    {
        /* POSIX test STRING: true when STRING is non-empty. */
        result = argv[pos][0] != '\0';
    }
    else if (remaining == 2)
    {
        const char *op = argv[pos];
        const char *arg = argv[pos + 1];

        if (strcmp(op, "-n") == 0)
            result = arg[0] != '\0';
        else if (strcmp(op, "-z") == 0)
            result = arg[0] == '\0';
        else if (strcmp(op, "-e") == 0 ||
                 strcmp(op, "-f") == 0 ||
                 strcmp(op, "-d") == 0 ||
                 strcmp(op, "-s") == 0)
        {
            result = test_path_predicate(session, op, arg);
        }
        else
        {
            valid = false;
        }
    }
    else if (remaining == 3)
    {
        const char *lhs = argv[pos];
        const char *op = argv[pos + 1];
        const char *rhs = argv[pos + 2];

        if (strcmp(op, "=") == 0 || strcmp(op, "==") == 0)
        {
            result = strcmp(lhs, rhs) == 0;
        }
        else if (strcmp(op, "!=") == 0)
        {
            result = strcmp(lhs, rhs) != 0;
        }
        else if (strcmp(op, "-eq") == 0 ||
                 strcmp(op, "-ne") == 0 ||
                 strcmp(op, "-lt") == 0 ||
                 strcmp(op, "-le") == 0 ||
                 strcmp(op, "-gt") == 0 ||
                 strcmp(op, "-ge") == 0)
        {
            long long a = 0, b = 0;
            if (!test_parse_integer(lhs, &a) ||
                !test_parse_integer(rhs, &b))
            {
                valid = false;
            }
            else if (strcmp(op, "-eq") == 0)
                result = a == b;
            else if (strcmp(op, "-ne") == 0)
                result = a != b;
            else if (strcmp(op, "-lt") == 0)
                result = a < b;
            else if (strcmp(op, "-le") == 0)
                result = a <= b;
            else if (strcmp(op, "-gt") == 0)
                result = a > b;
            else
                result = a >= b;
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }

    if (!valid)
    {
        printf("usage: %s\n",
               bracket ? "[ ! ] | [ STRING ] | [ -e|-f|-d|-s PATH ] | "
                         "[ -n|-z STRING ] | [ A =|!= B ] | "
                         "[ N -eq|-ne|-lt|-le|-gt|-ge N ]"
                       : "test [!] EXPRESSION");
        return 2;
    }

    if (negate)
        result = !result;
    return result ? 0 : 1;
}

static int cmd_sleep(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    if (argc != 2)
        return usage(tdsh_command_find("sleep"));
    char *end = NULL;
    double seconds = strtod(argv[1], &end);
    if (!end || *end || seconds < 0.0)
        return usage(tdsh_command_find("sleep"));
    double millis = seconds * 1000.0;
    if (millis > 4294967295.0)
        return 1;
    tdsh_sleep_ms((uint32_t)millis);
    return 0;
}


static int cmd_platform(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("platform"));
    printf("platform: %s\n", tdsh_platform_name());
    printf("TinyDesk Shell: %s\n", TDSH_VERSION);
    return 0;
}


static int cmd_whoami(tdsh_session_t *session, int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("whoami"));
    printf("%s\n", session->username);
    return 0;
}

static int cmd_free(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("free"));
    tdsh_memory_stats_t st;
    tdsh_memory_get_stats(&st);
    printf("Shell core heap: live=%u blocks / %u bytes, peak=%u blocks / %u bytes, allocs=%u, failures=%u\n",
           (unsigned)st.live_blocks, (unsigned)st.live_bytes,
           (unsigned)st.peak_blocks, (unsigned)st.peak_bytes,
           (unsigned)st.total_allocations, (unsigned)st.failed_allocations);
    return 0;
}


static int cmd_uptime(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("uptime"));
    uint64_t sec = tdsh_monotonic_ms() / 1000ULL;
    printf("%llu days %02llu:%02llu:%02llu\n",
           (unsigned long long)(sec / 86400ULL),
           (unsigned long long)((sec / 3600ULL) % 24ULL),
           (unsigned long long)((sec / 60ULL) % 60ULL),
           (unsigned long long)(sec % 60ULL));
    return 0;
}


static int cmd_set(tdsh_session_t *session, int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("set"));
    printf("USER=%s\nHOME=%s\nPWD=%s\nHOSTNAME=%s\n", session->username, session->home, session->cwd, session->hostname);
    for (size_t i = 0; i < TDSH_MAX_VARS; ++i)
    {
        if (session->vars[i].used)
            printf("%s=%s\n", session->vars[i].name, session->vars[i].value);
    }
    return 0;
}

static int cmd_unset(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 2)
        return usage(tdsh_command_find("unset"));
    int rc = 0;
    for (int i = 1; i < argc; ++i)
        if (tdsh_var_unset(session, argv[i]) != 0)
            rc = 1;
    return rc;
}

static int cmd_tdsh(tdsh_session_t *session, int argc, char **argv)
{
    if (argc < 3 || strcmp(argv[1], "run") != 0)
        return usage(tdsh_command_find("tdsh"));
    bool bg = false;
    if (argc == 4 && strcmp(argv[3], "--bg") == 0)
        bg = true;
    else if (argc != 3)
        return usage(tdsh_command_find("tdsh"));
    return tdsh_run_script(session, argv[2], bg);
}

static int cmd_version(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    (void)argv;
    if (argc != 1)
        return usage(tdsh_command_find("version"));
    printf("TinyDesk Shell %s (%s)\n", TDSH_VERSION, tdsh_platform_name());
    return 0;
}

/* peek and poke: the core checks every access against the port's regions,
 * so a port only lists what is safe. */

/* Decimal or 0x hexadecimal, as in the board configuration (never octal). */
static bool mem_number(const char *text, uint64_t *out)
{
    unsigned base = 10;
    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X'))
    {
        base = 16;
        text += 2;
    }
    if (!*text)
        return false;
    uint64_t value = 0;
    for (; *text; ++text)
    {
        unsigned digit;
        if (*text >= '0' && *text <= '9')
            digit = (unsigned)(*text - '0');
        else if (base == 16 && *text >= 'a' && *text <= 'f')
            digit = (unsigned)(*text - 'a' + 10);
        else if (base == 16 && *text >= 'A' && *text <= 'F')
            digit = (unsigned)(*text - 'A' + 10);
        else
            return false;
        if (value > (UINT64_MAX - digit) / base)
            return false;
        value = value * base + digit;
    }
    *out = value;
    return true;
}

/* "-w 8|16|32" before the operands: stores the width in bytes (32-bit by
 * default) and returns the index of the first operand, or -1. */
static int mem_width(int argc, char **argv, unsigned *bytes)
{
    *bytes = 4;
    if (argc < 2 || strcmp(argv[1], "-w") != 0)
        return 1;
    if (argc < 3)
        return -1;
    if (strcmp(argv[2], "8") == 0)
        *bytes = 1;
    else if (strcmp(argv[2], "16") == 0)
        *bytes = 2;
    else if (strcmp(argv[2], "32") != 0)
        return -1;
    return 3;
}

static const char *mem_name(const tdsh_mem_region_t *region)
{
    return region->name ? region->name : "?";
}

static uint32_t mem_width_flag(unsigned bytes)
{
    if (bytes == 1)
        return TDSH_MEM_8;
    if (bytes == 2)
        return TDSH_MEM_16;
    return TDSH_MEM_32;
}

/* Why region r does not allow the access, or NULL when it does; the text is
 * printed after "<cmd>: ". */
static const char *mem_refusal(const tdsh_mem_region_t *r, uint64_t address, uint64_t length, unsigned bytes,
                               bool write, char *buf, size_t cap)
{
    uint64_t start = r->start;
    uint64_t size = r->size;
    if (length > size - (address - start))
    {
        snprintf(buf, cap, "%" PRIu64 " bytes from 0x%" PRIx64 " cross the end of %s", length, address, mem_name(r));
        return buf;
    }
#if UINTPTR_MAX < UINT64_MAX
    if (address + length - 1 > UINTPTR_MAX)
    {
        snprintf(buf, cap, "%s lies past the end of the address space", mem_name(r));
        return buf;
    }
#endif
    if ((r->flags & mem_width_flag(bytes)) == 0)
    {
        snprintf(buf, cap, "%s does not allow %u-bit access", mem_name(r), bytes * 8);
        return buf;
    }
    if (write && (r->flags & TDSH_MEM_READONLY) != 0)
    {
        snprintf(buf, cap, "%s is read-only", mem_name(r));
        return buf;
    }
    return NULL;
}

/* True when one region allows all of [address, address + length) at this
 * width (regions may overlap: a writable window inside a read-only block);
 * otherwise prints why the first region holding the address refuses it. */
static bool mem_allowed(const char *cmd, uint64_t address, uint64_t length, unsigned bytes, bool write)
{
    if (address % bytes != 0)
    {
        printf("%s: 0x%" PRIx64 " is not aligned to %u bits\n", cmd, address, bytes * 8);
        return false;
    }
    size_t count;
    const tdsh_mem_region_t *r = mem_regions(&count);
    char why[128];
    const char *first = NULL;
    for (size_t i = 0; i < count; ++i)
    {
        if (address < r[i].start || address - r[i].start >= r[i].size)
            continue;
        char buf[128];
        const char *refusal = mem_refusal(&r[i], address, length, bytes, write, buf, sizeof(buf));
        if (!refusal)
            return true;
        if (!first)
        {
            snprintf(why, sizeof(why), "%s", refusal);
            first = why;
        }
    }
    if (first)
        printf("%s: %s\n", cmd, first);
    else
        printf("%s: 0x%" PRIx64 " is not in a region this port allows (peek -l)\n", cmd, address);
    return false;
}

static uint32_t mem_read(uintptr_t address, unsigned bytes)
{
    if (bytes == 1)
        return *(const volatile uint8_t *)address;
    if (bytes == 2)
        return *(const volatile uint16_t *)address;
    return *(const volatile uint32_t *)address;
}

static void mem_write(uintptr_t address, unsigned bytes, uint32_t value)
{
    if (bytes == 1)
        *(volatile uint8_t *)address = (uint8_t)value;
    else if (bytes == 2)
        *(volatile uint16_t *)address = (uint16_t)value;
    else
        *(volatile uint32_t *)address = value;
}

static int mem_list(void)
{
    size_t count;
    const tdsh_mem_region_t *r = mem_regions(&count);
    printf("%-16s %-18s %-18s %-9s %s\n", "REGION", "START", "END", "WIDTHS", "ACCESS");
    for (size_t i = 0; i < count; ++i)
    {
        if (r[i].size == 0)
            continue;
        char start[24], end[24], widths[12];
        snprintf(start, sizeof(start), "0x%08" PRIxPTR, r[i].start);
        snprintf(end, sizeof(end), "0x%08" PRIxPTR, (uintptr_t)(r[i].start + (r[i].size - 1)));
        snprintf(widths, sizeof(widths), "%s%s%s",
                 (r[i].flags & TDSH_MEM_8) ? "8 " : "",
                 (r[i].flags & TDSH_MEM_16) ? "16 " : "",
                 (r[i].flags & TDSH_MEM_32) ? "32 " : "");
        printf("%-16s %-18s %-18s %-9s %s\n", mem_name(&r[i]), start, end, widths,
               (r[i].flags & TDSH_MEM_READONLY) ? "read" : "read/write");
    }
    return 0;
}

static int cmd_peek(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    if (argc == 2 && strcmp(argv[1], "-l") == 0)
        return mem_list();

    unsigned bytes;
    int first = mem_width(argc, argv, &bytes);
    uint64_t address;
    uint64_t count = 1;
    if (first < 0 || argc - first < 1 || argc - first > 2 || !mem_number(argv[first], &address))
        return usage(tdsh_command_find("peek"));
    bool dump = argc - first == 2;
    if (dump && (!mem_number(argv[first + 1], &count) || count == 0 || count > UINT64_MAX / bytes))
        return usage(tdsh_command_find("peek"));
    if (!mem_allowed("peek", address, count * bytes, bytes, false))
        return 1;

    if (!dump)
    {
        /* Just the value, for V=$(peek ...) in scripts. */
        printf("0x%0*" PRIx32 "\n", (int)bytes * 2, mem_read((uintptr_t)address, bytes));
        return 0;
    }
    const uint64_t per_line = 16 / bytes;
    for (uint64_t n = 0; n < count; ++n)
    {
        uintptr_t at = (uintptr_t)(address + n * bytes);
        if (n % per_line == 0)
            printf("%s0x%08" PRIxPTR ":", n ? "\n" : "", at);
        printf(" %0*" PRIx32, (int)bytes * 2, mem_read(at, bytes));
    }
    printf("\n");
    return 0;
}

static int cmd_poke(tdsh_session_t *session, int argc, char **argv)
{
    (void)session;
    unsigned bytes;
    int first = mem_width(argc, argv, &bytes);
    uint64_t address;
    uint64_t value;
    if (first < 0 || argc - first != 2 || !mem_number(argv[first], &address) ||
        !mem_number(argv[first + 1], &value))
    {
        return usage(tdsh_command_find("poke"));
    }
    if (value > (UINT32_MAX >> (32 - bytes * 8)))
    {
        printf("poke: 0x%" PRIx64 " does not fit in %u bits\n", value, bytes * 8);
        return 1;
    }
    if (!mem_allowed("poke", address, bytes, bytes, true))
        return 1;
    mem_write((uintptr_t)address, bytes, (uint32_t)value);
    return 0;
}
