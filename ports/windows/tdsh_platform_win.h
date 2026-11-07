/*
 * tdsh_platform_win.h - start the TinyDesk Shell core on Windows.
 */
#ifndef TDSH_PLATFORM_WIN_H
#define TDSH_PLATFORM_WIN_H

#include "tdsh.h"

/* Create the sandbox tree under fs_root (root, home, tmp, etc), initialise
 * the core and register the portable built-in commands. Returns 0. */
int tdsh_win_init(const char *fs_root, const char *hostname);

/* The same for another default user (the standalone tdsh.exe uses the
 * Windows user name); also creates /home/<user>. */
int tdsh_win_init_user(const char *fs_root, const char *hostname, const char *user);

/* The standalone program: the Windows console as the shell's terminal
 * (UTF-8, VT sequences in and out, line editing), prompt and command loop.
 * Returns when the user types exit. */
int tdsh_win_run_interactive(tdsh_session_t *session);

/* For a command that handles Ctrl+C itself (py), in tdsh.exe's console:
 * raw input on or off (keys, Ctrl+C among them, arrive as VT bytes); true
 * once Ctrl+C was typed (the keys before it are dropped); the next key
 * (blocking, EOF at the end of input). */
void tdsh_console_raw_mode(bool on);
bool tdsh_break_requested(void);
int tdsh_getchar(void);

/* The Windows versions of the POSIX port's extra commands (ifconfig, ping,
 * date, cal, tz, write, hostpath, capabilities); called by tdsh_win_init(). */
int tdsh_win_register_commands(void);

#endif
