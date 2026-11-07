# Changelog

## Unreleased

* **MicroPython (moved from TinyDesk):** the `py` command and its port
  (`python/`: heap and stack, files through the shell's paths and rights,
  `machine` with Pin, ADC, PWM, I2C, SPI, UART and bitstream, frozen
  `asyncio` and `neopixel`) with the MicroPython 1.29.0 interpreter in
  `third_party/micropython` and the generated tables in `python/gen`.
  Applications add modules of their own: `tools/micropython/gen.sh` takes
  their sources, qstrs and manifest (`EXT_C`, `MANIFEST`, `OUT`), the PC
  builds call `tdsh_add_python()` (`python/tdsh_python.cmake`) and ESP-IDF
  projects replace the `micropython` component with one calling
  `tdsh_micropython_component()`; `td_py_add_cleanup()` and
  `HELP_EXTERNAL` let them release what a script left and describe their
  modules in `help()`. The generator also runs on Windows (Git Bash with
  MinGW-w64). See `python/README.md`.
* **`network` in `py` (read-only):** `isconnected()`, `ifconfig()`,
  `status()` (interface, addresses, MAC, Wi-Fi SSID, RSSI, channel) and
  `wait(timeout)` for scripts that start before the network is up.
  Connecting and settings stay with the shell's commands.
* **Network in `py`:** `socket` (`python/td_py_socket.c`: BSD sockets
  over the shell's network, IPv4 first in `getaddrinfo`, Ctrl+C and
  timeouts in blocking calls), `ssl`/`tls` (MicroPython's mbedTLS module,
  TLS 1.2; certificates checked against ESP-IDF's CA bundle on the boards
  and the system's root certificates on the PC, `python/td_py_tls_ca.c`),
  a blocking `websocket` client, and from micropython-lib (MIT) `requests`,
  `umqtt.simple`, `umqtt.robust` and `aiohttp` (`ssl` and `requests`
  changed to check certificates by default, `python/modules/`). The PC programs find
  mbedTLS in ESP-IDF (`TDSH_MBEDTLS_DIR`); without it they have sockets but
  no `ssl`. The generator needs MicroPython's `lib/micropython-lib`
  submodule and mbedTLS's headers (`IDF_PATH` or `MBEDTLS_INC`).
* **`py` banner:** "TinyDesk Shell" (`BOARD_NAME` in `tdsh_add_python()`
  and `tdsh_micropython_component()`; an application names itself).
* **`py` in the shell's own programs:** the firmware (ESP32-C6, ESP32,
  ESP32-S3) and the Linux and Windows programs register `py`
  (`TDSH_WITH_PYTHON`, on by default, for the PC builds). Ctrl+C stops a
  script on the serial/USB console, over SSH and in the PC terminal:
  `tdsh_break_requested()` and `tdsh_getchar()` (ESP-IDF, POSIX and
  Windows ports; keys typed before Ctrl+C are dropped, others are kept),
  `tdsh_ssh_break_requested()`, and on the PC `tdsh_console_raw_mode()`,
  as `py` puts the terminal in raw mode while it runs.
  `td_py_set_console()` gives `py` a console's key reader and raw mode.

* **Password hints (ESP-IDF port):** `useradd` and `passwd` ask for an
  optional hint after the password; one that contains the password is
  refused. `tdsh_user_hint_get()`, `tdsh_user_hint_set()` and
  `tdsh_hint_reveals()`; NVS `ush_users` / `hints`. Creating or deleting
  an account removes a hint left under its name. While root has the
  factory password its hint is `Type: TinyDesk`. See `docs/ACCOUNTS.md`.
* **Account roles and rights (ESP-IDF port):** every account other than
  root is an Admin or a User with rights: `users`, `system`, `network`,
  `hardware`, `shared`, `time` and `apps`. New Users get `apps`, new
  Admins everything but `hardware`; accounts from older firmware become
  Users with `apps`. `useradd NAME [admin|user]`, `userrole NAME
  [admin|user]` and `userrights NAME [+right|-right ...]` set them. An
  Admin with `users` may create, change and delete accounts whose rights
  it holds, never give more, and never change root or itself. Commands
  ask for rights with `TDSH_CMD_RIGHT()` (`reboot`: system; the Wi-Fi,
  `network`, `lan`, `ssh` and `ftp` commands: network; `gpio`, `hwtest`:
  hardware) and `TDSH_CMD_ADMIN_ONLY`. Roles live in a separate NVS key
  (`ush_users` / `access`) tied to each account's name and salt; the
  password database is unchanged. See `docs/ACCOUNTS.md`.
* **`/shared`:** made at start; accounts with `shared` may use it, while
  homes stay private and `/root` stays root's.
* **Sessions follow the account:** a password change or a recreated
  account ends that account's sessions (`tdsh: session expired; sign in
  again`).
* **Verified remembered desktop login:** `bootuser NAME` (root) also
  turns on remembered login for a desktop that consumes the account
  provider, but only after that account has logged in with its password
  (`ush_users` / `remember` and `proof`). A password change ends it;
  `bootuser --require-password` (or `off`) turns it off and erases the
  proof. Both work in `/root/.tdshrc.tdsh`.

* **The file system grows to its partition:** LittleFS is mounted with
  `grow_on_mount`, so a file system made for a smaller partition (by the
  Shell firmware's layout, say, before the Desktop firmware was flashed)
  grows to the whole partition at start, keeping its files. Before, the
  rest stayed unused: an ESP32-S3 had 1.9 MB of its 9.9 MB `/fs`.

## 0.2.0 (2026-10-31)

* **ESP32-S3 firmware:** `projects/esp32s3` builds TinyDesk Shell for any
  ESP32-S3 with 4 MB flash or more, on UART0 (the dev board's USB-UART
  port) at 115200 baud, with the classic ESP32's flash layout (2.5 MB
  application, 1.4 MB `/fs`). Octal PSRAM is used when the module has it
  (N16R8, N8R8). CI and the release build it; the release adds
  `tinydesk-shell-<version>-esp32s3-factory.bin` and its web installer
  manifest.
* **`peek` and `poke` on the ESP32-S3:** internal SRAM, RTC slow RAM, the
  mask ROM (32-bit reads) and the GPIO, IO_MUX and eFuse registers;
  `poke` writes the GPIO output registers, as on the other chips. PSRAM
  is not listed: the S3 maps it through its MMU at run time.

## 0.1.6 (2026-10-18)

* **nano with UTF-8 text:** the cursor moved by bytes, so Left, Right,
  Backspace and Delete stopped inside a character such as `é`, `ж` or `日`
  and Backspace left broken bytes behind. Now they move over and delete
  whole characters, Up and Down keep the character column, a typed
  character is read whole before it is drawn, long lines scroll by
  character, the status line and Ctrl+C count characters, search accepts
  UTF-8, and invalid bytes show as `?`. Each character takes one column,
  as in the line editor. Reported in tinydesk #4.
* **`peek` and `poke`** read and write memory, for RAM and peripheral
  registers: `peek -l`, `peek [-w 8|16|32] <address> [count]`,
  `poke [-w 8|16|32] <address> <value>`. Root only, 32-bit by default; one
  value prints alone (`V=$(peek ...)`), a count prints a dump of 16 bytes
  per line. Every access is checked against the regions the port lists
  with the new optional `mem_regions` hook in `tdsh_platform_api_t`:
  misaligned, outside or across a region's end, a width the region does
  not allow, or a write to a read-only region is refused with exit status
  1. Without the hook neither command is registered (the POSIX and
  Windows hosts). Requested in #1 for the TinyTang port.
* **`peek` and `poke` on the ESP32 and the ESP32-C6:** the ESP-IDF port
  lists its regions. `peek` reads internal RAM, RTC/LP RAM, the mask ROM,
  PSRAM (ESP32 with PSRAM) and the GPIO, IO_MUX and eFuse registers;
  `poke` writes only the GPIO output and output-enable registers (`OUT`
  to `ENABLE1_W1TC`), so RAM the firmware uses cannot be overwritten.
  Other chips have no table yet and no commands.
* **Overlapping memory regions:** an access is allowed when one region
  allows all of it, so a port can list a writable window inside a
  read-only block (the ESP32 `gpio_out` inside `gpio`). A refusal names
  the first region that holds the address.
* **Scripts that run out of memory while loading say so:**
  `uscript: <file>:<line>: not enough memory to load the script` (and a
  message for more than 1024 lines or a read error) instead of returning
  with status 2 and no output. From #2.
* **Builds on macOS:** `PTHREAD_STACK_MIN` comes from `<limits.h>`, with
  a fallback where it is missing (#5, by @mendeni).
* **Porting guide: file names.** FatFs volumes need long file names with
  the UTF-8 interface (`FF_LFN_UNICODE` 2); with ANSI/OEM, renaming or
  moving files with accented names can mix them up (tinydesk #8).
* **Ports can set the script memory limits:** `TDSH_MAX_VARS`,
  `TDSH_VAR_NAME_MAX`, `TDSH_VAR_VALUE_MAX` and `TDSH_SCRIPT_TASK_STACK`
  can be defined by the build. The defaults are unchanged: 64 variables,
  32-byte names, 256-byte values and 32768 bytes of stack per script
  worker. `TDSH_VAR_NAME_MAX` also limits function names in scripts.
  Every component that includes `tdsh.h` must use the same values (#4).

## 0.1.5 (2026-10-06)

* **STANDARDS.md** sets out the names, code style, commands, board keys,
  device paths and release rules, also for community ports.
* **Board configuration numbers** are decimal or `0x` hexadecimal, as
  documented: a leading zero no longer means octal (`08` was rejected and
  `010` read as 8).
* **`network mode`** and **`network autowifi`** with a value are root only;
  any user still sees them. Before, any user could switch Wi-Fi or the LAN
  off for the whole device, or make it connect at boot.

## 0.1.4 (2026-10-05)

* **`board save`** copies every setting that comes only from the firmware's
  built-in configuration into `/etc/board.conf` (the file's own lines and
  comments stay), so firmware built without them, such as an official
  release, keeps the board's pins. `board show` says when there are such
  settings. New `tdsh_board_unsaved()` and `tdsh_board_save_builtin()`.
* **Tab completion** skips directory entries whose names are too long for a
  shell path instead of copying them cut short (and the compiler no longer
  warns about it on Windows).
* **Long command lines:** a line longer than the terminal is wide wraps
  over several rows, and typing, Backspace, Delete, the arrows, Home/End
  and history redraw it correctly; before, the earlier rows were never
  cleared, so text was left behind or doubled, and the cursor could not
  move back across the wrap. Columns are counted in UTF-8 characters, not
  bytes. The width comes from the transport (`columns()` in
  `tdsh_terminal_io_t`: TIOCGWINSZ, the Windows console, the SSH pty,
  `tdsh_espidf_set_console_columns()`), else the terminal is asked once
  per line (`read_byte_timeout()`, ESC[6n), else 80.
* **Code style:** the C sources are formatted with `clang-format`
  (`.clang-format` in the repository root): braces on their own lines, one
  statement per line. Layout only; the code is unchanged.
* **Contributing:** a pre-commit hook (`.pre-commit-config.yaml`; set up with
  `pip install pre-commit` and `pre-commit install`) formats the C files of
  every commit with clang-format 16.0.6, the version CI checks with.
  `CONTRIBUTING.md` describes building, testing and formatting.

## 0.1.3 (2026-10-01)

* **nano follows the terminal's size** (asked with ESC[6n when it starts;
  80x24 without an answer, at most 80 columns). It assumed 80x24, so in a
  smaller terminal, such as a TinyDesk Terminal window, the status line
  (where Ctrl+C shows the cursor position) and the help lines were cut off.
  The help lines are clipped to the width. The Linux program's nano had
  the same layout and gets the same change.
* **The factory root password is named where it is needed:** `passwd`
  says the old password is `TinyDesk` while root still has it, and the `ssh`
  and `ftp` refusals name it (`TDSH_FACTORY_ROOT_PASSWORD` in
  `tdsh_espidf.h`).

## 0.1.2 (2026-09-28)

* **SD card at `/sd`** (`tdsh_sdcard.c`, command `sd`, root only): `sd
  mount | umount | format --yes | status` mounts a FAT card on the SPI bus
  (pins from the board configuration, shared with the W6100) in the VFS at
  `/sd`, and the shell's `/sd` maps to it, so the shell, `nano`, FTP and
  SFTP see it. `sd.automount = 1` mounts it at boot. `hwtest sd` tests on a
  mounted card instead of mounting it a second time. FAT long file names in
  UTF-8 are on in every ESP project (`sdkconfig.defaults`).
* **`ping -c <count>` on the boards** (1 to 100 requests per host, 4 by
  default), like the Windows and Linux programs; `ping -c` without a count
  shows the usage. The Linux program passes its default `-c 4` only when no
  `-c` is given.
* **`ping` output from a redirected session:** the replies and statistics
  were printed from ESP-IDF's ping task, so in TinyDesk's Terminal window
  only the first line appeared. The ping task now queues its lines and the
  session prints them.
* README: keep the checkout in a short folder on Windows (ESP-IDF's nested
  build folders pass the 260-character path limit).

## 0.1.1 (2026-09-28)

* **Windows program `tdsh.exe`** (`ports/windows`, `examples/windows`): the
  shell as a native Windows console program, for Windows Terminal. The line
  editor, history and Tab completion work as on Linux; `ifconfig`, `ping`,
  `date`, `cal`, `tz`, `write`, `hostpath`, `capabilities`. Its files are
  in `%LOCALAPPDATA%\tdsh\rootfs`, the user is the Windows user name.
  `docs/WINDOWS_HOST.md` describes it.
* The Windows port moved here from TinyDesk, which now uses it for its
  Windows Terminal window; `tdsh_win_init_user()` sets the default user.
* Releases also contain `tinydesk-shell-windows-x64.zip`; the host workflow
  builds and tests on Windows (MinGW) too.
* The release text takes its version from `VERSION` (`{version}` in
  `RELEASE_NOTES.md`).

## 0.1.0 (2026-09-28): first release

### Releases and documentation

* Releases: a tag `v<VERSION>` builds the ESP32-C6 and ESP32 firmware and the
  Linux program and attaches them to a draft pre-release
  (`.github/workflows/release.yml`, packaged by `tools/make_release.py` with
  the same file names as TinyDesk's Shell edition). The README links the web
  installer.
* Documentation: `docs/SCRIPTING.md`, the reference for `.tdsh` scripts
  (running them, variables and quoting, `$(…)` and `$((…))`, conditions,
  loops, functions, pipes and redirection, limits, a tested example), and
  a Scripts section in the README.

### Name, licence, layout

* The project is **TinyDesk Shell** (`tdsh`): C prefix `tdsh_`, macros
  `TDSH_`, Kconfig `CONFIG_TDSH_*`, ESP-IDF component `tdsh`, headers
  `tdsh.h`, `tdsh_espidf.h`, ... Released under the MIT licence.
* Scripts use the extension `.tdsh` and the shebang `#!/bin/tdsh`; a
  directory runs its `main.tdsh`; `tdsh run <file.tdsh|directory>`.
* Per-user files: `~/.tdshrc.tdsh` (startup script), `~/.tdsh_history`,
  `~/.tdsh_tz`.
* `third_party/wolfssh/ide/` (project files for other IDEs) is not bundled:
  its paths were too long for a Windows checkout.

### Firmware and platforms

* The repository root builds the ESP32-C6 firmware; **`projects/esp32`**
  builds the classic ESP32 firmware (4 MB flash, PSRAM optional, 2.5 MB
  app + 1.4 MB `/fs`: the layout of TinyDesk's 4 MB ESP32 desktop, so a
  board can switch between the two and keep its files). Both share `main/main.c`, which registers an example
  command, `hello`.
* The ESP-IDF console can be a **UART** (`CONFIG_ESP_CONSOLE_UART`) as well
  as USB Serial/JTAG.
* Each firmware embeds its `board.conf` (not in git) or
  `board.example.conf` as the built-in board configuration
  (`cmake/board_conf.cmake`).
* Classic ESP32: libsmb2's `MD5Init`/`MD5Update`/`MD5Final` come from the
  ROM (`src/tdsh_md5_rom.c`).
* A board without Ethernet no longer logs "Ethernet start:
  ESP_ERR_NOT_SUPPORTED" every second.
* CI: `.github/workflows/firmware.yml` builds both firmwares.

### Board configuration (new)

* `tdsh_board.h` / `src/core/tdsh_board.c`: a portable `key = value` store
  for hardware settings. Built-in text (`tdsh_espidf_config_t.board_config`,
  embedded by the application) is overridden by `/fs/etc/board.conf`,
  loaded right after the file system and before any module that reads it.
  Test: `tests/test_board.c`.
* Command `board [show|get|set|unset|init]` (`set`, `unset`, `init`: root).
* Ethernet reads the `eth.*` keys; without `eth.chip = w6100` the board has
  no Ethernet and no pin is touched. `lan hw set` and `lan poll` write the
  keys. The Kconfig pin defaults are -1 (fallbacks only).
* `hwtest` reads `sd.*`, `rs485.1.*` and `rs485.2.*`; unconfigured tests
  print `[SKIP]`. Built for every chip (the LP UART test only on the
  ESP32-C6).

### Users and security

* Factory root password `TinyDesk`; nothing forces a change.
* SSH: a per-device ECDSA P-256 host key, generated on the first start and
  kept in NVS (`tdsh_ssh` / `hostkey`); `ssh hostkey [new]` shows or
  replaces it. The built-in development key is only a fallback, which
  `ssh status` flags.
* `ssh` and `ftp`: `status` for everyone; start/stop/restart for root, or
  any user on the local console.
* SFTP for every user; non-root users are confined to their home
  (`wolfssh_local/sftp_jail.c`, wolfSSH's file macros routed through
  `tdsh_sftp_allowed()`).
* Saved Wi-Fi networks have owners (database version 2; a version 1
  database is converted on first load, its networks becoming shared).
  Root's networks are shared; other users add their own.

### API for applications (ESP-IDF)

* `tdsh_espidf_run_console()` runs the local console loop in the calling
  task with its stdin/stdout (TinyDesk runs it in a desktop window);
  `tdsh_espidf_console_set_user()` / `tdsh_espidf_console_user()` switch
  the console's user.
* Structured Wi-Fi API: `tdsh_wifi_scan_list()`, `tdsh_wifi_save()`,
  `tdsh_wifi_forget()`, `tdsh_wifi_connect_saved()`,
  `tdsh_wifi_disconnect_now()`.
* `tdsh_time_auto()`, `tdsh_time_set_auto()` (automatic SNTP time on/off,
  NVS `ush_time`/`auto`), `tdsh_time_sync_now()`.
* `tdsh_ssh_is_running()` / `tdsh_ssh_set_running()`,
  `tdsh_ftp_is_running()` / `tdsh_ftp_set_running()`.
* Script worker tasks inherit the caller's stdio (background workers only
  from the local console) and hand the global streams back before exiting.

### Fixes

* `ssh stop` works: the listening socket gets a 0.5 s `SO_RCVTIMEO`, so
  `accept()` returns and sees the stop (before, the server task stayed
  until the next client and `ssh start` failed).
* The SFTP start directory is set for password logins too (FileZilla could
  not open `/`).
* A half-done W6100 setup is undone (`eth_setup_undo()`): without a chip,
  every network retry leaked a driver task and an SPI device.
* The 64 KB SSH heap arena is no longer a static buffer: it is allocated on
  the first `ssh start`, from PSRAM when the chip has it (the start check
  then asks for 64 KB of internal RAM instead of 96 KB), else from internal
  RAM (the check adds the arena's 64 KB). Boards without PSRAM keep 64 KB of
  static RAM for everything else; `ssh status` shows where the heap is.
* The startup-file template no longer mentions a USB Serial/JTAG console on
  every board.
