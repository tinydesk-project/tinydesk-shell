# MicroPython (vendored, generated)

The interpreter behind TinyDesk Shell's `py` command:
[MicroPython](https://micropython.org) **v1.29.0**
(commit `0fd6c573ea815774668bbb16b8e197c8822368b2`), MIT licence (see
[LICENSE](LICENSE)).

Everything here except this README is copied by
[`tools/micropython`](../../tools/micropython/README.md) (`INTERPRETER=1`)
from a checkout of that release. Do not edit these files: change the
configuration in [`python/`](../../python/README.md) and regenerate.
One exception, re-apply it after `INTERPRETER=1`: `extmod/modtls_mbedtls.c`
prints mbedTLS's debug output only with `MICROPY_PY_SSL_DEBUG`, and calls
`MICROPY_PY_SSL_DEFAULT_CA` for every new `SSLContext` (the trusted CAs,
`python/td_py_tls_ca.c`); both places are marked "TinyDesk Shell". The
tables generated from the configuration are not here but in `python/gen`
(the shell's) or an application's own.

| Path | From MicroPython |
| --- | --- |
| `py/` | the core (all of `py/`, as MicroPython's embed port takes it) |
| `extmod/` | the modules the shell enables: `os`, `time`, `json`, `re`, `random`, `binascii`, `hashlib`, `heapq`, `select`, `_asyncio`, `tls` (mbedTLS), `machine` (the module and its ADC, PWM, UART, I2C, SPI, pulse and bitstream parts), the VFS layer and the POSIX file objects (plus all `extmod` headers) |
| `shared/` | the REPL (`pyexec`, `readline`), stdio and timing helpers |
| `drivers/bus/` | software SPI, for `machine.SoftSPI` |
| `lib/re1.5/` | the regular-expression engine `extmod/modre.c` includes |
| `lib/crypto-algorithms/` | SHA-256 for `hashlib` where mbedTLS is not built in (`extmod/modhashlib.c` includes it; public domain, by Brad Conte) |
| `sources.cmake` | the list of `.c` files, used by the PC and ESP-IDF builds |
