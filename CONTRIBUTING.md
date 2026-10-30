# Contributing to TinyDesk Shell

Bug reports and patches are welcome. Include the platform (ESP32 board,
Linux, Windows or another port), the terminal and the source revision when
reporting a problem.

1. Build and test on the PC:

       cmake -S . -B build-host -G Ninja -DTDSH_BUILD_HOST=ON
       cmake --build build-host
       ctest --test-dir build-host --output-on-failure

   On Windows add `-DCMAKE_C_COMPILER=gcc` (MinGW-w64).
2. If you touched ESP-IDF code, build the standalone firmware: `idf.py build`
   in the repository root (ESP32-C6), in `projects/esp32` and in
   `projects/esp32s3` (ESP-IDF 5.3.1).
3. Set up formatting once:

       pip install pre-commit
       pre-commit install

   Every commit then formats the C files you changed with clang-format 16.
   To format by hand instead: `pip install clang-format==16.0.6`, then
   `clang-format -i <files>`. If the format check fails on your pull
   request, don't worry: I can fix it before merging.
4. Describe what changed for users (commands, options, API) in the pull
   request, so the documentation and the changelog can follow.
5. Keep board-specific pins out of the code; use board configuration keys.

Names, code style, commands, board keys and release files follow
[STANDARDS.md](STANDARDS.md).

New platform ports go in `ports/<platform>/`; see `ports/posix` and
`ports/windows` for small examples. Ports for other chips are welcome;
STANDARDS.md says how to name one and what its README must state.

TinyDesk uses this repository as its `third_party/tdsh` submodule, so shell
changes land here first.

More detail: the [contributing guide](https://tinydesk-project.github.io/#/contributing)
in the TinyDesk documentation.

Security problems: report them privately via GitHub (Security → Report a
vulnerability). Contributions are released under the MIT licence.
