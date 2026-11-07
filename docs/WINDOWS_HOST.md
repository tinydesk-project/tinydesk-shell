# Windows host port (tdsh.exe)

`tdsh.exe` is TinyDesk Shell as a native Windows program: the same portable
core as the firmware and the POSIX host, with a Windows platform port. It
needs only Windows system DLLs. Releases ship it as
`tinydesk-shell-windows-x64.zip`; TinyDesk's Desktop edition for Windows
links the same port for its Terminal window.

Run it in Windows Terminal (or any console with VT sequences, Windows 10 or
later).

## Build

With MinGW-w64 GCC, CMake and Ninja:

```bash
cmake -S . -B build-host -G Ninja -DCMAKE_C_COMPILER=gcc -DTDSH_BUILD_HOST=ON
cmake --build build-host
ctest --test-dir build-host --output-on-failure
build-host/tdsh_host.exe
```

The release workflow adds `-DCMAKE_BUILD_TYPE=Release
-DCMAKE_EXE_LINKER_FLAGS=-static` and renames the program to `tdsh.exe`.
The tests are the console-access and board-configuration tests and a smoke
test that pipes a script through the program.

## Files

| Path | Contents |
| --- | --- |
| `ports/windows/tdsh_platform_win.c` | the platform API (clock, sleep, random bytes, worker threads) and the isolated filesystem: `tdsh_win_init_user()` |
| `ports/windows/tdsh_win_commands.c` | `ifconfig`, `ping`, `date`, `cal`, `tz`, `write`, `hostpath`, `capabilities` |
| `ports/windows/tdsh_win_compat.c`, `.h` | POSIX calls for MinGW and per-thread `stdin`/`stdout` (force-included into the core) |
| `ports/windows/tdsh_win_console.c` | the interactive console: VT input and output, UTF-8, the line editor |
| `examples/windows/main.c` | `tdsh.exe` itself |

## Isolated filesystem

Like the POSIX port, the Windows port does not use your real folders. The
shell's `/` is:

```text
%LOCALAPPDATA%\tdsh\rootfs
```

so `/home/alice/notes.txt` is
`%LOCALAPPDATA%\tdsh\rootfs\home\alice\notes.txt`. `hostpath <path>` shows
where a shell path is on the PC.

The shell user is your Windows user name and the host name is the
computer's, both in lower case with other characters than letters, digits,
`.`, `_` and `-` replaced by `_`. The user starts in `/home/<user>`.

## Console

The line editor is the portable one (see [POSIX_HOST.md](POSIX_HOST.md)):
Tab completion, Up/Down history (`~/.tdsh_history`), Left/Right, Home/End,
Ctrl+A/E/U/K/L/C, and lines that wrap at the console's width. The console is switched to VT input only while a line is
read and restored before a command runs. Input from a pipe or a file works
too (Windows line ends are accepted). Colour is on unless `NO_COLOR` is set.

`py` (MicroPython, built in unless `-DTDSH_WITH_PYTHON=OFF`) switches the
console to VT input while it runs, so its prompt edits its own line and
Ctrl+C stops a running script instead of closing `tdsh.exe`.

`ifconfig` lists the adapters that are up (name, MAC, IPv4 and IPv6
addresses) and `ping [-c N] host` sends IPv4 echo requests through the IP
Helper API. There is no `nano` on Windows.
