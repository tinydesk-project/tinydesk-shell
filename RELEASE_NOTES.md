# TinyDesk Shell developer preview

A Unix-like shell for microcontrollers, with users, networking and SSH, that
also runs on a PC. It is the shell inside
[TinyDesk](https://github.com/tinydesk-project/tinydesk) and works on its own too.

This release is a developer preview: expect rough edges, and please report
what breaks.

## New in 0.4.0

* **`wifiap`, the board's own Wi-Fi access point** (STA+AP): off, on, or on
  while there is no network; TinyDesk-XXXX and 192.168.4.1, a random
  password per board at first. SSH and FTP work over it.
* **SD card hot-plug:** a card mounts by itself when inserted and unmounts
  when pulled out (`sd.automount`, now on wherever the pins are set; the
  slot's card-detect switch with `sd.cd`), and gets `/sd/TinyDesk`.
  Accounts with the Shared right use `/sd` like `/shared`.

**Fixes**

* FTP answered "550 Invalid path" to everything since 0.3.0: its session
  lacked the account generation the shell checks.

## New in 0.3.1

* **`ssl` in the Linux and Windows programs:** 0.3.0's `tdsh_host` and
  `tdsh_host.exe` were built without TLS, so `py` had no `ssl` there (no
  HTTPS, MQTT over TLS or `upip`). They have it now, and a release build
  stops if it would leave it out (`TDSH_REQUIRE_TLS`). The firmware had it
  already; nothing else changed.

## New in 0.3.0

* **`py`, MicroPython, in the shell itself** (#6): scripts, the prompt,
  files with the shell's paths and rights, `machine` (pins and buses, for
  root), `asyncio`, Ctrl+C on the serial/USB console, over SSH and in the
  PC programs.
* **Network in Python:** `socket`, `ssl` (TLS 1.2 with certificate
  checks: the firmware's CA bundle, or the PC's roots), `requests`,
  `umqtt`, `websocket`, `aiohttp`, and `network` for the connection's state.
* **Packages and virtual environments:** `upip install | uninstall | list
  | freeze`, `venv`, `activate`, `deactivate`, `venvs` (from ushell).
* **`tdsh.shell()`** runs a shell command from Python.
* **API stability:** `STABILITY.md`; the public C API, the Python modules
  and the board keys are recorded and checked by the tests; internal
  declarations moved to `tdsh_espidf_internal.h`. `TDSH_VERSION_MAJOR`,
  `_MINOR`, `_PATCH`.

Earlier: the ESP32-S3 image and `peek`/`poke` on it (0.2.0); nano with UTF-8 text, `peek` and `poke` on the ESP32
and the ESP32-C6, script memory limits for small boards and a message
when a script runs out of memory, and builds on macOS (0.1.6); only root
changes the network policy, and board configuration numbers are decimal
or `0x` hexadecimal (0.1.5); long
command lines wrap and stay editable, and
`board save` keeps built-in pins (0.1.4); nano follows the terminal's
size (0.1.3); the SD card at `/sd` (`sd mount`, 0.1.2); `ping -c`, and
`tdsh.exe`, a native Windows program (`tinydesk-shell-windows-x64.zip`).

## Install

* **ESP boards, from the browser:** <https://tinydesk-project.github.io/install/#shell/esp32c6>
  (Chrome or Edge on a computer). Choose *TinyDesk Shell* and your board.
* **Without the browser:** flash a `*-factory.bin` below at offset 0:

  ```bash
  esptool.py --chip esp32c6 write_flash 0x0 tinydesk-shell-{version}-esp32c6-factory.bin
  esptool.py --chip esp32 write_flash 0x0 tinydesk-shell-{version}-esp32-factory.bin
  esptool.py --chip esp32s3 write_flash 0x0 tinydesk-shell-{version}-esp32s3-factory.bin
  ```

* **Linux (x86_64, built on Ubuntu 22.04):** `tinydesk-shell-linux-x86_64.tar.gz`,
  then `./tdsh`. Its files live in `~/.local/share/tdsh/rootfs`.
* **Windows (x64, Windows 10 or later):** `tinydesk-shell-windows-x64.zip`, then
  `tdsh.exe` in Windows Terminal. Its files live in `%LOCALAPPDATA%\tdsh\rootfs`.

| File | Board |
| --- | --- |
| `tinydesk-shell-{version}-esp32c6-factory.bin` | ESP32-C6 with 8 MB flash, built-in USB |
| `tinydesk-shell-{version}-esp32-factory.bin` | any ESP32 with 4 MB flash or more; PSRAM is used when present |
| `tinydesk-shell-{version}-esp32s3-factory.bin` | any ESP32-S3 with 4 MB flash or more, on its USB-UART port; Octal PSRAM is used when present |

Check the files against `SHA256SUMS.txt`. The firmware is not signed. A
factory image erases users, Wi-Fi networks and the SSH host key.

## Before connecting

Open the board's serial port in a UTF-8 terminal (115200 baud on the
ESP32 and ESP32-S3, any speed on the ESP32-C6's USB port), or the web terminal at
<https://tinydesk-project.github.io/console/>. You start as root:
run `passwd` locally (initial password: `TinyDesk`) before enabling remote
access. `help` lists the commands; `.tdsh` scripts are described in
`docs/SCRIPTING.md`.

Changes: see `CHANGELOG.md`.
