/*
 * td_py_tdsh.c - the `tdsh` module: the shell from a script.
 *
 *   tdsh.shell(line)    run a shell command line; returns its exit status
 *   tdsh.version()      the shell's version, "0.4.0"
 *   tdsh.getvar(name)   a shell variable of the session (VIRTUAL_ENV, ...), or None
 *   tdsh.user()         the session's user
 *   tdsh.home()         the user's home directory (a shell path)
 *
 * shell() runs in the script's session, with the script user's rights,
 * starting from the script's current directory; a `cd` in it does not move
 * the shell or the script. Its output goes where print() goes. An
 * application can offer the same function in its own module
 * (td_py_shell_obj, td_py_tdsh.h): TinyDesk's tinydesk.shell() is this one.
 */
#include <stdio.h>
#include <string.h>

#include "extmod/vfs.h"
#include "py/mperrno.h"
#include "py/runtime.h"
#include "td_py.h"
#include "td_py_tdsh.h"

static mp_obj_t td_py_shell(mp_obj_t line_in)
{
    const char *line = mp_obj_str_get_str(line_in);
    tdsh_session_t *session = td_py_session();
    if (!session)
        mp_raise_OSError(MP_EIO);
    const char *cwd = mp_obj_str_get_str(mp_vfs_getcwd());
    char saved[TDSH_MAX_PATH];
    memcpy(saved, session->cwd, sizeof(saved));
    snprintf(session->cwd, sizeof(session->cwd), "%s", cwd);
    int status = tdsh_execute_line(session, line);
    memcpy(session->cwd, saved, sizeof(saved));
    return MP_OBJ_NEW_SMALL_INT(status);
}
MP_DEFINE_CONST_FUN_OBJ_1(td_py_shell_obj, td_py_shell);

static mp_obj_t td_py_tdsh_version(void)
{
    return mp_obj_new_str(TDSH_VERSION, strlen(TDSH_VERSION));
}
static MP_DEFINE_CONST_FUN_OBJ_0(td_py_tdsh_version_obj, td_py_tdsh_version);

static tdsh_session_t *session_or_raise(void)
{
    tdsh_session_t *session = td_py_session();
    if (!session)
        mp_raise_OSError(MP_EIO);
    return session;
}

static mp_obj_t td_py_tdsh_getvar(mp_obj_t name)
{
    const char *v = tdsh_var_get(session_or_raise(), mp_obj_str_get_str(name));
    return v ? mp_obj_new_str(v, strlen(v)) : mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(td_py_tdsh_getvar_obj, td_py_tdsh_getvar);

static mp_obj_t td_py_tdsh_user(void)
{
    const char *u = session_or_raise()->username;
    return mp_obj_new_str(u, strlen(u));
}
static MP_DEFINE_CONST_FUN_OBJ_0(td_py_tdsh_user_obj, td_py_tdsh_user);

static mp_obj_t td_py_tdsh_home(void)
{
    const char *h = session_or_raise()->home;
    return mp_obj_new_str(h, strlen(h));
}
static MP_DEFINE_CONST_FUN_OBJ_0(td_py_tdsh_home_obj, td_py_tdsh_home);

static const mp_rom_map_elem_t td_py_tdsh_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_tdsh)},
    {MP_ROM_QSTR(MP_QSTR_shell), MP_ROM_PTR(&td_py_shell_obj)},
    {MP_ROM_QSTR(MP_QSTR_version), MP_ROM_PTR(&td_py_tdsh_version_obj)},
    {MP_ROM_QSTR(MP_QSTR_getvar), MP_ROM_PTR(&td_py_tdsh_getvar_obj)},
    {MP_ROM_QSTR(MP_QSTR_user), MP_ROM_PTR(&td_py_tdsh_user_obj)},
    {MP_ROM_QSTR(MP_QSTR_home), MP_ROM_PTR(&td_py_tdsh_home_obj)},
};
static MP_DEFINE_CONST_DICT(td_py_tdsh_globals, td_py_tdsh_table);

const mp_obj_module_t td_py_tdsh_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&td_py_tdsh_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tdsh, td_py_tdsh_module);
