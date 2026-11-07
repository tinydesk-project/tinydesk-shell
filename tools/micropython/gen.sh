#!/bin/sh
# Regenerate MicroPython's generated headers and frozen modules (and, with
# INTERPRETER=1, the interpreter in third_party/micropython). See README.md.
#
#   tools/micropython/gen.sh /path/to/micropython [VAR=value ...]
#
# Without variables: the shell's own python/gen. An application with
# modules of its own passes EXT_C, EXT_CFLAGS, EXT_QSTR_DEFS, MANIFEST and
# OUT (see the Makefile). The checkout must be the release named in
# third_party/micropython/README.md (or the one you are moving to, with
# INTERPRETER=1). Needs make, gcc and python3: Linux, WSL, or Git Bash on
# Windows with MinGW-w64 and Python 3.
set -e
if [ $# -lt 1 ] || [ ! -f "$1/py/mkenv.mk" ]; then
    echo "usage: $0 /path/to/micropython [VAR=value ...]" >&2
    exit 2
fi
top=$(cd "$1" && pwd)
shift
cd "$(dirname "$0")"
native=
case "$(uname -s)" in
MINGW* | MSYS*)
    # Windows, Git Bash with MinGW-w64 (make, gcc) and Python 3: Windows
    # paths for make, python for python3, mpy-cross.exe. Keep the checkout
    # on a short path (the generator's command lines get long).
    top=$(cd "$top" && pwd -W)
    native="PYTHON=python MPY_CROSS=$top/mpy-cross/build/mpy-cross.exe"
    ;;
esac
make clean MICROPYTHON_TOP="$top" $native "$@" >/dev/null
make MICROPYTHON_TOP="$top" $native "$@"
# One line ending in the generated files, whichever system made them.
for v in "$@"; do case "$v" in OUT=*) out=${v#OUT=} ;; esac; done
out=${out:-../../python/gen}
sed -i 's/\r$//' "$out"/genhdr/*.h "$out"/frozen/*.c
# Windows' makemanifest names the frozen files with backslashes.
sed -i '/original source file/s|\\|/|g' "$out"/frozen/*.c
echo "Done. Check: git status python/gen third_party/micropython (or your OUT)"
