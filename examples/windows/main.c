/*
 * The standalone TinyDesk Shell for Windows (tdsh.exe).
 *
 * Its files live in %LOCALAPPDATA%\tdsh\rootfs, apart from your real ones
 * (the Linux program uses ~/.local/share/tdsh/rootfs). You are the Windows
 * user, the host name is the computer's.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdsh_platform_win.h"
#ifdef TD_WITH_PYTHON
#include "td_py.h"
#endif

/* A shell user or host name: lower case, letters, digits, '.', '_', '-'. */
static void clean_name(const char *in, char *out, size_t cap, const char *fallback)
{
    size_t n = 0;
    for (const char *p = in ? in : ""; *p && n + 1 < cap; p++)
    {
        unsigned char c = (unsigned char)*p;
        out[n++] = (isalnum(c) || c == '.' || c == '_' || c == '-') ? (char)tolower(c) : '_';
    }
    out[n] = '\0';
    if (!n)
        snprintf(out, cap, "%s", fallback);
}

int main(void)
{
    char base[TDSH_MAX_REAL_PATH], root[TDSH_MAX_REAL_PATH];
    const char *appdata = getenv("LOCALAPPDATA");
    snprintf(base, sizeof(base), "%s/tdsh", appdata && appdata[0] ? appdata : ".");
    for (char *p = base; *p; p++)
        if (*p == '\\')
            *p = '/';
    snprintf(root, sizeof(root), "%s/rootfs", base);
    /* Create every missing folder up to rootfs's parent (errors show below). */
    for (char *p = base + 1; *p; p++)
    {
        if (*p != '/' || p[-1] == ':')
            continue;
        *p = '\0';
        mkdir(base, 0755);
        *p = '/';
    }
    mkdir(base, 0755);

    char user[TDSH_USERNAME_MAX], host[TDSH_HOSTNAME_MAX];
    clean_name(getenv("USERNAME"), user, sizeof(user), "developer");
    clean_name(getenv("COMPUTERNAME"), host, sizeof(host), "windows");

    int rc = tdsh_win_init_user(root, host, user);
    if (rc != 0)
    {
        fprintf(stderr, "tdsh: cannot set up %s (error %d)\n", root, rc);
        return 1;
    }
#ifdef TD_WITH_PYTHON
    /* py: the console goes raw while it runs, so Ctrl+C stops a script. */
    td_py_register_shell_command();
    td_py_set_break_check(tdsh_break_requested);
    td_py_set_console(tdsh_getchar, tdsh_console_raw_mode);
#endif
    tdsh_session_t session;
    rc = tdsh_session_init(&session, user, true);
    if (rc != 0)
    {
        fprintf(stderr, "tdsh: session start failed (%d)\n", rc);
        return 1;
    }
    printf("TinyDesk Shell %s - Windows\nType 'help' for commands, 'exit' to leave.\n", TDSH_VERSION);
    printf("Isolated TinyDesk Shell files: %s\n\n", root);
    return tdsh_win_run_interactive(&session);
}
