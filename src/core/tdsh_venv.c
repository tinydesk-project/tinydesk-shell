/*
 * tdsh_venv.c - Python virtual environments (from ushell's venvs).
 *
 *   venv DIR          make a virtual environment: DIR/lib for its packages
 *                     and DIR/venv.json, the record of what upip installed
 *   activate DIR      use it in this session: py puts DIR/lib first on
 *                     sys.path and upip installs there; the prompt shows (name)
 *   deactivate        back to the user's own ~/lib (/lib for root)
 *   venvs             the environments made with venv (* the active one)
 *
 * The active environment is the session variable VIRTUAL_ENV (a shell
 * path), as in CPython's venv, so a script can test it and a new session
 * starts without one. The environments a user made are listed in
 * ~/.venvs, one path a line; ones that were removed are skipped.
 */
#include "tdsh.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define VENV_FILE "venv.json"
#define REGISTRY  "~/.venvs"

/* The environment's name: the last part of its path. */
static const char *base_name(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash && slash[1] ? slash + 1 : path;
}

void tdsh_prompt_prefix(tdsh_session_t *session, char *out, size_t cap)
{
    if (!out || cap == 0)
        return;
    out[0] = '\0';
    const char *env = session ? tdsh_var_get(session, "VIRTUAL_ENV") : NULL;
    if (env && env[0])
        snprintf(out, cap, "(%s) ", base_name(env));
}

/* DIR as a shell path and a real one; whether it holds a venv.json. */
static bool resolve(tdsh_session_t *session, const char *dir, char *logical, char *real, bool *is_venv)
{
    if (tdsh_path_to_real(session, dir, real, TDSH_MAX_REAL_PATH, logical, TDSH_MAX_PATH) != 0)
        return false;
    if (is_venv)
    {
        char file[TDSH_MAX_REAL_PATH + sizeof(VENV_FILE) + 2];
        struct stat st;
        snprintf(file, sizeof(file), "%s/%s", real, VENV_FILE);
        *is_venv = stat(file, &st) == 0 && S_ISREG(st.st_mode);
    }
    return true;
}

/* Add path to ~/.venvs (once). */
static void remember(tdsh_session_t *session, const char *logical)
{
    char real[TDSH_MAX_REAL_PATH], line[TDSH_MAX_PATH + 2];
    if (tdsh_path_to_real(session, REGISTRY, real, sizeof(real), NULL, 0) != 0)
        return;
    FILE *f = fopen(real, "r");
    if (f)
    {
        while (fgets(line, sizeof(line), f))
        {
            line[strcspn(line, "\r\n")] = '\0';
            if (!strcmp(line, logical))
            {
                fclose(f);
                return;
            }
        }
        fclose(f);
    }
    f = fopen(real, "a");
    if (f)
    {
        fprintf(f, "%s\n", logical);
        fclose(f);
    }
}

static int cmd_venv(tdsh_session_t *session, int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: venv DIR\n");
        return 2;
    }
    char logical[TDSH_MAX_PATH], real[TDSH_MAX_REAL_PATH];
    bool is_venv = false;
    if (!resolve(session, argv[1], logical, real, &is_venv))
    {
        printf("venv: bad path %s\n", argv[1]);
        return 2;
    }
    if (is_venv)
    {
        printf("venv: %s is already a virtual environment\n", logical);
        return 1;
    }
    char lib[TDSH_MAX_REAL_PATH + 8], file[TDSH_MAX_REAL_PATH + sizeof(VENV_FILE) + 2];
    snprintf(lib, sizeof(lib), "%s/lib", real);
    snprintf(file, sizeof(file), "%s/%s", real, VENV_FILE);
    if ((mkdir(real, 0755) != 0 && errno != EEXIST) || (mkdir(lib, 0755) != 0 && errno != EEXIST))
    {
        printf("venv: cannot create %s: %s\n", logical, strerror(errno));
        return 1;
    }
    FILE *f = fopen(file, "w");
    if (!f)
    {
        printf("venv: cannot write %s/%s: %s\n", logical, VENV_FILE, strerror(errno));
        return 1;
    }
    fprintf(f, "{\"name\": \"%s\", \"packages\": {}}\n", base_name(logical));
    fclose(f);
    remember(session, logical);
    printf("Created %s. Use it with: activate %s\n", logical, argv[1]);
    return 0;
}

static int cmd_activate(tdsh_session_t *session, int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: activate DIR\n");
        return 2;
    }
    char logical[TDSH_MAX_PATH], real[TDSH_MAX_REAL_PATH];
    bool is_venv = false;
    if (!resolve(session, argv[1], logical, real, &is_venv) || !is_venv)
    {
        printf("activate: %s is not a virtual environment (make one with: venv %s)\n", argv[1], argv[1]);
        return 1;
    }
    if (tdsh_var_set(session, "VIRTUAL_ENV", logical) != 0)
    {
        printf("activate: no room for the variable\n");
        return 1;
    }
    return 0;
}

static int cmd_deactivate(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (!tdsh_var_get(session, "VIRTUAL_ENV"))
    {
        printf("deactivate: no virtual environment is active\n");
        return 1;
    }
    tdsh_var_unset(session, "VIRTUAL_ENV");
    return 0;
}

static int cmd_venvs(tdsh_session_t *session, int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char real[TDSH_MAX_REAL_PATH], line[TDSH_MAX_PATH + 2];
    const char *active = tdsh_var_get(session, "VIRTUAL_ENV");
    int n = 0;
    if (tdsh_path_to_real(session, REGISTRY, real, sizeof(real), NULL, 0) == 0)
    {
        FILE *f = fopen(real, "r");
        if (f)
        {
            while (fgets(line, sizeof(line), f))
            {
                line[strcspn(line, "\r\n")] = '\0';
                char lg[TDSH_MAX_PATH], rl[TDSH_MAX_REAL_PATH];
                bool is_venv = false;
                if (!line[0] || !resolve(session, line, lg, rl, &is_venv) || !is_venv)
                    continue;   /* removed since */
                printf("%c %s\n", active && !strcmp(active, lg) ? '*' : ' ', lg);
                n++;
            }
            fclose(f);
        }
    }
    if (!n)
        printf("No virtual environments. Make one with: venv DIR\n");
    return 0;
}

static const tdsh_command_t s_venv_commands[] = {
    {"venv", "venv DIR", "Make a Python virtual environment (DIR/lib, DIR/venv.json)", cmd_venv, 0},
    {"activate", "activate DIR", "Use a Python virtual environment in this session", cmd_activate, 0},
    {"deactivate", "deactivate", "Stop using the active virtual environment", cmd_deactivate, 0},
    {"venvs", "venvs", "List the virtual environments you made", cmd_venvs, 0},
};

int tdsh_register_venv_commands(void)
{
    return tdsh_register_commands(s_venv_commands, sizeof(s_venv_commands) / sizeof(s_venv_commands[0]));
}
