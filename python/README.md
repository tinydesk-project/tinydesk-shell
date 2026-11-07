# MicroPython in TinyDesk Shell

The `py` command runs MicroPython scripts and a prompt in a shell session:
`py FILE [ARG...]`, `py -c CODE`, or `py` alone for the prompt. Files use
the shell's paths and rights; Ctrl+C stops a script; `machine` and
`neopixel` (pins and buses) are for root.

| Where | What |
| --- | --- |
| `python/td_py.c` | the `py` command: heap, stack, running a file, `-c` or the prompt, Ctrl+C, help |
| `python/td_py_vfs.c` | files: `open()`, `os` through the shell's paths and rights |
| `python/td_py_machine.c`, `td_py_machine_*.h` | `machine`: Pin, ADC, PWM, I2C, SPI, UART, bitstream |
| `python/hw/` | the chip side of `machine` (`td_py_hw_esp.c`; `td_py_hw_host.c` on a PC) |
| `python/mpconfigport.h`, `qstrdefsport.h` | the interpreter's configuration |
| `python/manifest.py`, `modules/` | frozen Python: `asyncio`, `neopixel` |
| `python/gen/` | the generated tables and frozen modules (tools/micropython) |
| `third_party/micropython/` | the interpreter (MicroPython's own sources) |
| `python/tdsh_python.cmake` | PC builds: `tdsh_add_python()` |
| `ports/esp_idf/components/micropython/` | the ESP-IDF component |

An application registers the command once, before sessions start:

```c
#include "td_py.h"

td_py_register_shell_command();       /* py */
td_py_set_break_check(break_pressed);  /* Ctrl+C stops a script */
```

The shell's own programs do this in `main/main.c` (firmware: the serial/USB
console and SSH, with `tdsh_break_requested` and `tdsh_getchar`) and
`examples/posix`, `examples/windows` (which also pass
`tdsh_console_raw_mode` to `td_py_set_console`, so the terminal is raw while
`py` runs). The PC builds include it unless `-DTDSH_WITH_PYTHON=OFF`.

## Modules of your own

An application built on the shell (TinyDesk's desktop is one) can add
Python modules: C files with `MP_REGISTER_MODULE`, and frozen Python.
MicroPython lists every module and name in tables generated at build time,
so the application generates its own `gen/` with the shell's generator and
builds with that instead of `python/gen`:

```sh
third_party/tdsh/tools/micropython/gen.sh /path/to/micropython \
    EXT_C="my/mod_a.c my/mod_b.c" EXT_CFLAGS="-Imy -Imy/include" \
    EXT_QSTR_DEFS=my/qstrdefs.h MANIFEST=my/manifest.py \
    MANIFEST_VARS="MY_DIR=$PWD/my" OUT=my/gen
```

Its `manifest.py` starts with `include("$(TDSH_PY_DIR)/manifest.py")` to
keep the shell's frozen modules. Then:

* PC: `tdsh_add_python(NAME my_python GEN_DIR my/gen EXTRA_SRCS my/mod_a.c ... LINK tdsh ...)`
  from `python/tdsh_python.cmake`;
* ESP-IDF: a component named `micropython` in a component directory listed
  after the shell's, whose `CMakeLists.txt` calls
  `tdsh_micropython_component(GEN_DIR ... EXTRA_SRCS ... EXTRA_INCLUDES ... EXTRA_REQUIRES ...)`
  from `ports/esp_idf/components/micropython/micropython_component.cmake`.

To describe the extra modules in `help()`, the application defines
`const char td_py_help_text[]` itself and builds with `HELP_EXTERNAL` (both
functions take it). At run time, `td_py_add_cleanup()` releases what a
script left behind (TinyDesk closes its windows).

Regenerate (the shell's `python/gen`, or your `OUT`) after changing
`mpconfigport.h`, a `MP_QSTR_`/`MP_REGISTER_MODULE`/`MP_REGISTER_ROOT_POINTER`
in a module source, a manifest or a qstrdefs file: see
[tools/micropython/README.md](../tools/micropython/README.md).
