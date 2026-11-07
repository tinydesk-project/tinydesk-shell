# Python modules frozen into TinyDesk Shell's MicroPython (compiled to
# bytecode by tools/micropython into python/gen/frozen). An application
# with modules of its own includes this file from its manifest:
#   include("$(TDSH_PY_DIR)/manifest.py")

# asyncio; its C part (_asyncio) and select are built in (mpconfigport.h).
package(
    "asyncio",
    ("__init__.py", "core.py", "event.py", "funcs.py", "lock.py", "stream.py"),
    base_path="$(MPY_DIR)/extmod",
    opt=3,
)

# neopixel: RGB LED strips through machine.bitstream.
module("neopixel.py", base_path="$(TDSH_PY_DIR)/modules", opt=3)
