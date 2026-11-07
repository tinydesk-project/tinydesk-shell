#ifndef TDSH_POSIX_H
#define TDSH_POSIX_H

#include <stdbool.h>
#include "tdsh.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    const char *hostname;
    const char *default_user;
    const char *fs_root;
    const char *host_home;
    bool map_default_user_home_to_host_home;
    bool register_core_builtins;
    bool register_posix_commands;
} tdsh_posix_config_t;

#define TDSH_POSIX_CONFIG_DEFAULT()                  \
    {                                                \
        .hostname = "localhost",                     \
        .default_user = NULL,                        \
        .fs_root = NULL,                             \
        .host_home = NULL,                           \
        .map_default_user_home_to_host_home = false, \
        .register_core_builtins = true,              \
        .register_posix_commands = true,             \
    }

int tdsh_posix_init(const tdsh_posix_config_t *config);
int tdsh_posix_run_interactive(void);
int tdsh_posix_register_commands(void);

/* For a command that handles Ctrl+C itself (py) on the program's terminal:
 * raw mode on or off (keys, Ctrl+C among them, arrive as bytes); true once
 * Ctrl+C was typed (the keys before it are dropped, the others stay for
 * tdsh_getchar); the next key (blocking, EOF at the end of input). */
void tdsh_console_raw_mode(bool on);
bool tdsh_break_requested(void);
int tdsh_getchar(void);
const char *tdsh_posix_real_fs_root(void);
const tdsh_platform_api_t *tdsh_posix_platform(void);

#ifdef __cplusplus
}
#endif

#endif
