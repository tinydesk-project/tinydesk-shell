# Porting TinyDesk Shell

Implement `tdsh_platform_api_t` and provide a filesystem/VFS supporting the
standard C calls used by core (`fopen`, `stat`, `opendir`, `rename`, etc.).

Minimum useful hooks:
1. monotonic milliseconds;
2. sleep/yield;
3. random bytes;
4. optional allocator family;
5. worker/thread primitive when dedicated-stack/background scripts are needed.

A single-threaded target can leave `worker_run` null: foreground scripts run
synchronously and background scripts report unsupported.

## File names

The shell passes file names to the filesystem as UTF-8 and shows them as
UTF-8. A FatFs volume (an SD card) needs long file names with the UTF-8
interface: `FF_USE_LFN` 1 to 3 and `FF_LFN_UNICODE` 2 in `ffconf.h` (on
ESP-IDF, `CONFIG_FATFS_LFN_HEAP` and `CONFIG_FATFS_API_ENCODING_UTF_8`,
which the ESP32 projects set). With the default ANSI/OEM interface, names
with characters outside the code page (`á`, `ő`) are converted back and
forth and can end up on the wrong file when files are renamed or moved
(tinydesk #8).

## Memory access: peek and poke

`peek` and `poke` let root read and write memory, for inspecting RAM and
peripheral registers. The core registers them only when the port fills in
the optional `mem_regions` hook and it returns at least one region; the
POSIX and Windows ports leave it null, so they do not have the commands.
The ESP-IDF port lists regions for the ESP32, the ESP32-C6 and the ESP32-S3
(`idf_mem_regions()` in `ports/esp_idf/components/tdsh/src/tdsh_platform_espidf.c`):
RAM and ROM read-only, the GPIO, IO_MUX and eFuse registers read-only,
and only the GPIO output registers writable. The port lists the regions, the core does the rest: parsing,
checks, the access itself and the output. The addresses below are examples:

```c
static const tdsh_mem_region_t s_regions[] = {
    {"sram", 0x62FC0000u, 0x40000u, TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32},
    {"gpio", 0x2000C000u, 0x100u, TDSH_MEM_32},
    {"rom", 0x90000000u, 0x20000u, TDSH_MEM_8 | TDSH_MEM_16 | TDSH_MEM_32 | TDSH_MEM_READONLY},
};

static const tdsh_mem_region_t *my_mem_regions(void *context, size_t *count)
{
    (void)context;
    *count = sizeof(s_regions) / sizeof(s_regions[0]);
    return s_regions;
}
```

Set `.mem_regions = my_mem_regions` in the port's `tdsh_platform_api_t`
before `tdsh_register_core_builtins()` runs. Every access is checked before
memory is touched: the address must be aligned to the width, the whole
access must lie in one region, the region must allow that width, and `poke`
must not write a `TDSH_MEM_READONLY` region. Anything else is refused with
exit status 1. Regions may overlap: the access is allowed when any one
region allows all of it, so a small writable window can sit inside a
read-only block (list both; the order does not matter). A refusal names
the first region that holds the address.

What to list:

- RAM, with every width. Writing RAM the firmware is using can crash it;
  list such RAM read-only if `poke` should not reach it.
- Peripheral registers that are safe to read at any time, with only the
  widths the hardware accepts (many accept only aligned 32-bit access).

Leave out registers that change state when read (clear-on-read status
registers, FIFOs: a `peek` would lose data), and peripherals that may be
clock-gated or powered down (an access can hang the bus or fault). A wrong
access can still crash the board, so a crash record or watchdog helps.

Do not spread target `#ifdef`s through `src/core`. Add a new port directory and
run the same host conformance tests against the unchanged core.
