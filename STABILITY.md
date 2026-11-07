# API stability

From 1.0, TinyDesk Shell follows [semantic versioning](https://semver.org):
an application, script or board configuration made for 1.x keeps working
on every later 1.x release.

| Version | May |
| --- | --- |
| patch (1.0.1) | fix bugs; no API change |
| minor (1.1.0) | add functions, types, struct members at the end, constants, commands, Python names, board keys |
| major (2.0.0) | remove or change anything public |

`TDSH_VERSION` is the version as text, `TDSH_VERSION_MAJOR`, `_MINOR` and
`_PATCH` as numbers for `#if`.

## What is public

| Part | Where | Checked by (ctest) |
| --- | --- | --- |
| C API | `include/*.h`, `ports/esp_idf/components/tdsh/include/tdsh_espidf.h`, `ports/posix/tdsh_posix.h`, `ports/windows/tdsh_platform_win.h`, `python/td_py.h`, `python/td_py_tdsh.h` | `tdsh_api_stable`: `tools/check_api.py` against `api/tdsh.api` |
| Python in `py` | `tdsh`, `network`, `socket`, `ssl`, `machine`, `neopixel`, `websocket`, `requests`, `umqtt.simple`, `umqtt.robust`, `aiohttp` | `tdsh_py_contract`: `tools/check_py_contract.py` against `python/py_contract.json` |
| board.conf keys | the keys in [`docs`](docs) and on the site's board configuration page | `tdsh_board_keys`: `tools/check_board_keys.py` against `api/board_keys.txt` |
| Commands | names, options and exit statuses in `docs/FUNCTIONS.md` | (reviews) |
| Stored data | accounts, Wi-Fi networks and settings in NVS, `/fs` files | (migrations keep reading older data) |

Not public, free to change in any release: `src/`, everything under
`ports/esp_idf/components/tdsh/src/` (its shared declarations are in
`tdsh_espidf_internal.h`: the built-in commands' handlers, start/stop
routines, console and SSH helpers), the generated tables in `python/gen`,
and the exact text a command prints (scripts should use exit statuses).
MicroPython's own modules follow MicroPython's releases.

## Changing the API

The checks fail on any difference, so every change is deliberate and shows
in the diff of the recorded file:

```sh
python tools/check_api.py --record api/tdsh.api <the headers above>   # the C API
python tools/check_py_contract.py --record path/to/tdsh_host          # Python
python tools/check_board_keys.py --record api/board_keys.txt src ports main python
```

Within 1.x, a recorded change may only add. Something to retire is marked
deprecated in its comment and in the changelog, keeps working, and goes in
the next major version. A struct that applications allocate gets new
members only at its end.
