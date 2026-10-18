# TinyDesk Shell developer preview

A Unix-like shell for microcontrollers, with users, networking and SSH, that
also runs on a PC. It is the shell inside
[TinyDesk](https://github.com/tinydesk-project/tinydesk) and works on its own too.

This release is a developer preview: expect rough edges, and please report
what breaks.

## New in 0.1.6

* **nano with UTF-8 text:** Left, Right, Backspace and Delete move over
  and delete whole characters, so text such as `Привет` or `日本語` no
  longer breaks into stray bytes; Up and Down keep the column, and the
  column shown counts characters (tinydesk #4).
* **`peek` and `poke`:** root can read RAM, ROM, PSRAM and the GPIO,
  IO_MUX and eFuse registers of the ESP32 and the ESP32-C6, and write the
  GPIO output registers; `peek -l` lists what is allowed. Other ports
  list their own regions through the new `mem_regions` hook (#1).
* **Scripts on small boards:** ports can set the script memory limits
  (`TDSH_MAX_VARS`, `TDSH_VAR_NAME_MAX`, `TDSH_VAR_VALUE_MAX`,
  `TDSH_SCRIPT_TASK_STACK`), and a script that runs out of memory while
  it loads says so instead of stopping silently (#2, #4).
* **Builds on macOS** (#5, by @mendeni).

Also since 0.1.0: only root changes the network policy, and board
configuration numbers are decimal or `0x` hexadecimal (0.1.5); long
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
  ```

* **Linux (x86_64, built on Ubuntu 22.04):** `tinydesk-shell-linux-x86_64.tar.gz`,
  then `./tdsh`. Its files live in `~/.local/share/tdsh/rootfs`.
* **Windows (x64, Windows 10 or later):** `tinydesk-shell-windows-x64.zip`, then
  `tdsh.exe` in Windows Terminal. Its files live in `%LOCALAPPDATA%\tdsh\rootfs`.

| File | Board |
| --- | --- |
| `tinydesk-shell-{version}-esp32c6-factory.bin` | ESP32-C6 with 8 MB flash, built-in USB |
| `tinydesk-shell-{version}-esp32-factory.bin` | any ESP32 with 4 MB flash or more; PSRAM is used when present |

Check the files against `SHA256SUMS.txt`. The firmware is not signed. A
factory image erases users, Wi-Fi networks and the SSH host key.

## Before connecting

Open the board's serial port in a UTF-8 terminal (115200 baud on the
ESP32, any speed on the ESP32-C6's USB port), or the web terminal at
<https://tinydesk-project.github.io/console/>. You start as root:
run `passwd` locally (initial password: `TinyDesk`) before enabling remote
access. `help` lists the commands; `.tdsh` scripts are described in
`docs/SCRIPTING.md`.

Changes: see `CHANGELOG.md`.
