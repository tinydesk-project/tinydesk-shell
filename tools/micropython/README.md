# Generating MicroPython

TinyDesk Shell builds MicroPython from the interpreter's own sources in
[`third_party/micropython`](../../third_party/micropython/README.md) and
the shell's port in [`python/`](../../python/README.md). MicroPython also
needs tables generated from the configuration: the qstr table (every name
the interpreter knows), the list of built-in modules, the root pointers,
and the frozen Python modules (`asyncio`, `neopixel`), compiled to bytecode.
The shell's are in `python/gen`; an application with modules of its own
generates its own (`EXT_C`, `MANIFEST`, `OUT`, see the `Makefile` and
`python/README.md`).

Regenerate them after changing any of these:

* [`python/mpconfigport.h`](../../python/mpconfigport.h) (features and
  modules);
* a `MP_QSTR_...`, `MP_REGISTER_MODULE` or `MP_REGISTER_ROOT_POINTER` in
  `python/*.c` (or in an application's module sources);
* [`python/manifest.py`](../../python/manifest.py) (the frozen modules) or
  [`qstrdefsport.h`](../../python/qstrdefsport.h);
* the MicroPython release: then also `INTERPRETER=1`, which replaces
  `third_party/micropython` (except its README; update the version there).

It needs make, gcc and Python 3: Linux, WSL, or Git Bash on Windows with
MinGW-w64 (keep the checkout on a short path there, the generator's command
lines get long). The checkout needs its `lib/micropython-lib` submodule
(the frozen `ssl`, `umqtt`, `requests` and `aiohttp`), and the generator
needs mbedTLS's headers for `ssl`: ESP-IDF's, found through `IDF_PATH`, or
`MBEDTLS_INC=/path/to/mbedtls/include`:

```bash
git clone --depth 1 --branch v1.29.0 https://github.com/micropython/micropython.git ../mp
git -C ../mp submodule update --init lib/micropython-lib
tools/micropython/gen.sh ../mp                      # python/gen
tools/micropython/gen.sh ../mp INTERPRETER=1        # and third_party/micropython
```

`gen.sh` runs this directory's `Makefile` (MicroPython's own build rules,
the way its `ports/embed` does it). The first run also builds `mpy-cross`
in the checkout, which compiles the frozen modules; the same `mpy-cross`
makes `.mpy` files for `py`. The output has LF line endings and the same
content on every system. Commit it with the change that needed it.

The preprocessor here runs without the build's platform macros (it defines
`TD_PY_GENHDR`), so code inside `#ifdef ESP_PLATFORM` or `#ifdef _WIN32`
must not use qstrs: a name only one platform sees would be missing from the
table. Names the generator cannot see in use go in `qstrdefsport.h`: the
ones from code that needs mbedTLS (`hashlib.sha1`, `hashlib.md5`), and
names with escaped characters such as `MP_QSTR__slash_lib` ("/lib").
`TD_PY_GENHDR` also turns on every native-code emitter the shell uses
(Xtensa, RISC-V, x64), so the tables have the names of each.

The generator reads `python/*.c` (and the `td_py_machine_*.h` files that
MicroPython's `extmod/machine_*.c` include), so those must not include
ESP-IDF headers outside `#ifdef ESP_PLATFORM`: the `machine` module's
Python side calls the plain-C interface `td_py_hw.h`, whose
implementations live in `python/hw/` (`td_py_hw_esp.c` with ESP-IDF's
drivers, `td_py_hw_host.c` for the PC programs), which the generator does
not read.
