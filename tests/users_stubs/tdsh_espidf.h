#ifndef USERS_TEST_ESP_H
#define USERS_TEST_ESP_H
#define TDSH_MOUNT_POINT "users-test-fs"
#include "tdsh.h"
#include "nvs.h"
#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif
#define TDSH_USERNAME_MAX          32
#define TDSH_FACTORY_ROOT_PASSWORD "TestFactoryOnly"
#define TDSH_FACTORY_HINT          "Type: " TDSH_FACTORY_ROOT_PASSWORD
#define TDSH_STARTUP_FILE          ".tdshrc.tdsh"
typedef struct
{
    char name[TDSH_USERNAME_MAX];
    tdsh_role_t role;
    uint32_t rights;
} tdsh_user_info_t;
bool tdsh_user_exists(const char *);
bool tdsh_user_authenticate(const char *, const char *);
uint32_t tdsh_user_login(const char *, const char *);
tdsh_role_t tdsh_user_role(const char *);
uint32_t tdsh_user_rights(const char *);
int tdsh_user_create(const char *, const char *, const char *, tdsh_role_t, uint32_t);
int tdsh_user_password_set(const char *, const char *, const char *, const char *);
#define TDSH_HINT_MAX 64
int tdsh_user_hint_get(const char *, char *, size_t);
int tdsh_user_hint_set(const char *, const char *, const char *);
bool tdsh_hint_reveals(const char *, const char *);
int tdsh_boot_user_get(char *, size_t);
int tdsh_boot_login_require_password(void);
int tdsh_console_readline(const char *, char *, size_t, bool);
int tdsh_session_set_user(tdsh_session_t *, const char *);
int tdsh_session_set_user_generation(tdsh_session_t *, const char *, uint32_t);
int tdsh_run_user_startup(tdsh_session_t *);
bool tdsh_is_local_console_task(void);
bool tdsh_console_begin_recovery(void);
void tdsh_console_end_recovery(void);
void tdsh_netmount_remove_owner(const char *);
#endif
