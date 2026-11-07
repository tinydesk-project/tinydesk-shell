/*
 * td_py_tdsh.h - for applications' Python modules: the shell() function of
 * the tdsh module (td_py_tdsh.c), to offer it in a module of their own.
 */
#ifndef TD_PY_TDSH_H
#define TD_PY_TDSH_H

#include "py/obj.h"

/* shell(line) -> exit status */
extern const mp_obj_fun_builtin_fixed_t td_py_shell_obj;

#endif /* TD_PY_TDSH_H */
