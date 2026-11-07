# POSIX / WSL host port

Build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
ctest --test-dir build --output-on-failure
./build/tdsh_host
```

## Isolated filesystem

The POSIX port detects the current Linux username/hostname, but **does not map
the TinyDesk Shell home onto the real Linux `$HOME` by default**. TinyDesk Shell remains a
sandboxed runtime just like the embedded build.

Default backing root:

```text
$HOME/.local/share/tdsh/rootfs
```

For a Linux user `alice`, the logical TinyDesk Shell path:

```text
/home/alice/test.txt
```

is normally backed by:

```text
/home/alice/.local/share/tdsh/rootfs/home/alice/test.txt
```

It is **not** `/home/alice/test.txt`.

Use `hostpath` to inspect the backing path:

```text
hostpath
hostpath test.txt
hostpath /tmp
```

`map_default_user_home_to_host_home` still exists as an explicit integration
option for host applications that intentionally want host-home passthrough,
but `TDSH_POSIX_CONFIG_DEFAULT()` keeps it `false`.

## Interactive terminal editing

The POSIX shell uses the portable TinyDesk Shell VT100 line editor rather than `fgets`.
It supports:

- Tab command completion
- Tab file/directory completion
- Up/Down persistent history (`~/.tdsh_history` inside the sandbox)
- Left/Right cursor movement
- Home/End
- Delete and Backspace
- Ctrl+A / Ctrl+E
- Ctrl+U / Ctrl+K
- Ctrl+L
- lines longer than the terminal is wide: they wrap over several rows, and
  editing anywhere in them redraws every row (the width comes from
  `TIOCGWINSZ`; UTF-8 characters count as one column each)
- Ctrl+C

The POSIX port switches the TTY to raw mode only while reading a command line
and restores the previous terminal settings before executing the command. This
allows normal commands and the full-screen `nano` command to manage their own
terminal behavior safely.

`py` (MicroPython, built in unless `-DTDSH_WITH_PYTHON=OFF`) puts the
terminal in raw mode while it runs, so its prompt edits its own line and
Ctrl+C stops a running script instead of ending the program.

Color is enabled only when stdout is an ANSI-capable TTY. Set `NO_COLOR=1` to
disable it.

Run `capabilities` inside TinyDesk Shell to see which functions are native to the
POSIX port and which belong to ESP-IDF or another optional platform module.
