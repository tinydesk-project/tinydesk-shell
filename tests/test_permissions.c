#include "tdsh.h"
#undef NDEBUG /* the checks are asserts: keep them in Release builds */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
static uint32_t shared_rights;
static tdsh_role_t role(const char *u)
{
    return !strcmp(u, "admin") ? TDSH_ROLE_ADMIN : TDSH_ROLE_USER;
}
static uint32_t rights(const char *u)
{
    return !strcmp(u, "admin") ? TDSH_RIGHTS_ADMIN : shared_rights | TDSH_RIGHT_APPS;
}
static int ok(tdsh_session_t *s, int argc, char **argv)
{
    (void)s;
    (void)argc;
    (void)argv;
    return 23;
}
int main(void)
{
    tdsh_core_config_t cfg = TDSH_CORE_CONFIG_DEFAULT();
    cfg.user_role = role;
    cfg.user_rights = rights;
    assert(!tdsh_core_init(&cfg));
    tdsh_session_t user, admin, root;
    assert(!tdsh_session_init(&user, "alice", true));
    assert(!tdsh_session_init(&admin, "admin", true));
    assert(!tdsh_session_init(&root, "root", true));
    assert(tdsh_session_role(&user) == TDSH_ROLE_USER);
    assert(tdsh_session_role(&admin) == TDSH_ROLE_ADMIN);
    assert(tdsh_session_role(&root) == TDSH_ROLE_ROOT);
    assert(!tdsh_session_has_right(&user, TDSH_RIGHT_USERS));
    assert(tdsh_session_has_right(&admin, TDSH_RIGHT_USERS));
    assert(!tdsh_session_has_right(&admin, TDSH_RIGHT_HARDWARE));
    assert(tdsh_session_has_right(&root, TDSH_RIGHT_ALL));
    tdsh_command_t a = {"admincmd", "admincmd", "test", ok, TDSH_CMD_ADMIN_ONLY}, r = {"rootcmd", "rootcmd", "test", ok, TDSH_CMD_ROOT_ONLY}, n = {"netcmd", "netcmd", "test", ok, TDSH_CMD_RIGHT(TDSH_RIGHT_NETWORK)};
    assert(!tdsh_register_command(&a));
    assert(!tdsh_register_command(&r));
    assert(!tdsh_register_command(&n));
    assert(tdsh_execute_line(&user, "admincmd") == 126);
    assert(tdsh_execute_line(&admin, "admincmd") == 23);
    assert(tdsh_execute_line(&admin, "rootcmd") == 126);
    assert(tdsh_execute_line(&root, "rootcmd") == 23);
    assert(tdsh_execute_line(&user, "netcmd") == 126);
    shared_rights = TDSH_RIGHT_NETWORK;
    assert(tdsh_execute_line(&user, "netcmd") == 23);
    char path[TDSH_MAX_PATH];
    assert(tdsh_path_normalize(&admin, "/root", path, sizeof(path)) == -EACCES);
    assert(tdsh_path_normalize(&user, "/root/.tdshrc.tdsh", path, sizeof(path)) == -EACCES);
    assert(tdsh_path_normalize(&user, "/shared/a", path, sizeof(path)) == -EACCES);
    shared_rights |= TDSH_RIGHT_SHARED;
    assert(!tdsh_path_normalize(&user, "/shared/a", path, sizeof(path)));
    assert(!strcmp(path, "/shared/a"));
    snprintf(user.cwd, sizeof(user.cwd), "/shared");
    assert(!tdsh_path_normalize(&user, "../../../root/pass", path, sizeof(path)));
    assert(!strcmp(path, "/shared/root/pass"));
    assert(!tdsh_path_normalize(&user, "~/notes", path, sizeof(path)));
    assert(!strcmp(path, "/home/alice/notes"));
    /* The SD card is shared like /shared: in it, out of it, never above it. */
    assert(!tdsh_path_normalize(&user, "/sd/photos/a.ppm", path, sizeof(path)));
    assert(!strcmp(path, "/sd/photos/a.ppm"));
    snprintf(user.cwd, sizeof(user.cwd), "/sd/photos");
    assert(!tdsh_path_normalize(&user, "../../root/pass", path, sizeof(path)));
    assert(!strcmp(path, "/sd/root/pass"));
    assert(!tdsh_path_normalize(&user, "/shared/a", path, sizeof(path)));
    assert(!tdsh_path_normalize(&user, "/sdx", path, sizeof(path)));   /* not the card: */
    assert(!strcmp(path, "/home/alice/sdx"));                          /* into the home */
    snprintf(user.cwd, sizeof(user.cwd), "/shared");
    shared_rights = TDSH_RIGHT_NETWORK;
    assert(tdsh_path_normalize(&user, "/sd/a", path, sizeof(path)) == -EACCES);
    shared_rights = 0;
    assert(tdsh_path_normalize(&user, "file", path, sizeof(path)) == -EACCES);
    assert(tdsh_path_normalize(&user, "..\\..\\root", path, sizeof(path)) == -EINVAL);
    assert(tdsh_path_normalize(&user, "C:/root", path, sizeof(path)) == -EINVAL);
    return 0;
}
