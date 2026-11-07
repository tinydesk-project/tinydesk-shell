# MicroPython in TinyDesk Shell

The `py` command runs MicroPython scripts and a prompt in a shell session:
`py FILE [ARG...]`, `py -c CODE`, or `py` alone for the prompt. Files use
the shell's paths and rights; Ctrl+C stops a script; `machine` and
`neopixel` (pins and buses) are for root.

| Where | What |
| --- | --- |
| `python/td_py.c` | the `py` command: heap, stack, running a file, `-c` or the prompt, Ctrl+C, help |
| `python/td_py_vfs.c` | files: `open()`, `os` through the shell's paths and rights |
| `python/td_py_socket.c` | `network` (status) and `socket`: BSD sockets over the network the shell set up (lwIP, or the PC's) |
| `python/td_py_tls_ca.c` | the CAs `ssl`/`tls` trust by default (the firmware's bundle, the PC's roots) |
| `python/td_py_machine.c`, `td_py_machine_*.h` | `machine`: Pin, ADC, PWM, I2C, SPI, UART, bitstream |
| `python/hw/` | the chip side of `machine` (`td_py_hw_esp.c`; `td_py_hw_host.c` on a PC) |
| `python/mpconfigport.h`, `qstrdefsport.h` | the interpreter's configuration |
| `python/manifest.py`, `modules/` | frozen Python: `asyncio`, `neopixel`, `websocket`; from micropython-lib `ssl`, `umqtt`, `requests`, `aiohttp` |
| `python/gen/` | the generated tables and frozen modules (tools/micropython) |
| `third_party/micropython/` | the interpreter (MicroPython's own sources) |
| `python/tdsh_python.cmake` | PC builds: `tdsh_add_python()` |
| `ports/esp_idf/components/micropython/` | the ESP-IDF component |

## Network

Scripts use the network the shell already set up (Wi-Fi or Ethernet on a
board, the PC's on Linux and Windows). They can read its state, not change
it.

| Module | What |
| --- | --- |
| `network` | read-only status: `isconnected()`, `ifconfig()` (ip, netmask, gateway, dns), `status()` (a dict: interface, connected, ip, netmask, gateway, dns, mac, and for Wi-Fi ssid, rssi, channel), `wait(timeout=None)` (seconds; `True` once connected, Ctrl+C stops it). On a PC only the address is known. Connecting and settings stay with the shell's commands |
| `socket` | `getaddrinfo`, `socket()` with `connect`, `bind`, `listen`, `accept`, `send(all)`, `recv`, `sendto`, `recvfrom`, `settimeout`, `setblocking`, `setsockopt`; a stream (`read`, `readline`, `write`) for `ssl`, `select` and `asyncio`. Addresses are `(host, port)`; `getaddrinfo` lists IPv4 first |
| `ssl`, `tls` | TLS 1.2 (mbedTLS). `ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)` and `tls.SSLContext(...)` check the server's certificate against the trusted CAs (a bad one raises `ValueError` or `OSError`); `ssl.wrap_socket()` does not unless `cert_reqs=ssl.CERT_REQUIRED` (MicroPython's default) |
| `requests` | HTTP and HTTPS: `requests.get(url).json()`, `post`, ... Checks certificates; `verify=False` does not |
| `umqtt.simple`, `umqtt.robust` | MQTT 3.1.1 client: `MQTTClient(id, host, port=8883, ssl=ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT))` for TLS, `connect`, `publish`, `subscribe`, `check_msg` |
| `websocket` | blocking WebSocket client: `create_connection("wss://...", timeout=10)`, `send`, `recv`, `close` (checks certificates; `verify=False` does not) |
| `aiohttp` | asyncio HTTP client and `ws_connect` WebSockets (checks certificates) |

`ssl` and `requests` are micropython-lib's with one change each, so that
they check certificates by default as CPython does (`python/modules/`);
`umqtt` and `aiohttp` are frozen unchanged.

```python
import requests, websocket
from umqtt.simple import MQTTClient

print(requests.get("https://example.com/").status_code)
ws = websocket.create_connection("wss://echo.websocket.org/"); ws.send("hi"); print(ws.recv())
c = MQTTClient("tdsh", "broker.hivemq.com"); c.connect(); c.publish(b"demo/topic", b"hello")
```

A blocking call (`connect`, `recv`, `accept`) waits in 10 ms slices, so
Ctrl+C stops it; a timeout raises `OSError(ETIMEDOUT)`. Sockets a script
leaves open are closed when it ends. DNS lookups wait for the resolver.
The PC programs have `ssl` when built with mbedTLS (found in ESP-IDF, or
`-DTDSH_MBEDTLS_DIR=...`); without it, sockets work and `ssl` raises
ImportError.

## Registering the command

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

An application's product name for the banner and
`sys.implementation._machine` is `BOARD_NAME` in both build functions
(default "TinyDesk Shell"; TinyDesk passes "TinyDesk").

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
