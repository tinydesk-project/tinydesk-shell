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

# websocket: a small blocking WebSocket client (create_connection).
# requests and ssl: micropython-lib's, changed to check certificates by
# default (see the top of each file).
package("requests", base_path="$(TDSH_PY_DIR)/modules", opt=3)
module("ssl.py", base_path="$(TDSH_PY_DIR)/modules", opt=3)
module("websocket.py", base_path="$(TDSH_PY_DIR)/modules", opt=3)

# upip (the shell's `upip` command) and the mip installer it uses. mip by
# path: its manifest would also freeze micropython-lib's requests.
module("upip.py", base_path="$(TDSH_PY_DIR)/modules", opt=3)
package("mip", base_path="$(MPY_LIB_DIR)/micropython/mip", opt=3)

# Networking from micropython-lib ($(MPY_DIR)/lib/micropython-lib, MIT):
# the MQTT clients and the asyncio HTTP/WebSocket client.
# umqtt directly: its manifest would also freeze micropython-lib's ssl.
package("umqtt", ("simple.py",), base_path="$(MPY_LIB_DIR)/micropython/umqtt.simple", opt=3)
package("umqtt", ("robust.py",), base_path="$(MPY_LIB_DIR)/micropython/umqtt.robust", opt=3)
require("aiohttp", opt=3)
