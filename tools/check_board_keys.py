"""check_board_keys.py - the board.conf keys the code reads against a list.

    python tools/check_board_keys.py LIST SRC_DIR...              check
    python tools/check_board_keys.py --record LIST SRC_DIR...     write the list
    python tools/check_board_keys.py --doc PAGE.md LIST           keys the page does not describe

A key counts when the code passes it to tdsh_board_get/int/bool/origin/set
as a string literal, or builds it with snprintf in a file that reads board
keys ("rs485.%d.uart" is listed as rs485.N.uart). tests/ and third-party
code are skipped. Within 1.x a key keeps its name and meaning; new keys may
be added (record them, and describe them in the board configuration page).
"""
import os
import re
import sys

CALL = re.compile(r'tdsh_board_(?:get|int|bool|origin|set)\s*\(\s*"([a-z0-9_]+(?:\.[a-z0-9_]+)+)"')
BUILT = re.compile(r'"([a-z0-9_]+(?:\.(?:[a-z0-9_]+|%d))+)"')
SKIP = ("tests", "third_party", "managed_components", "build", ".git")


def keys_in(dirs):
    keys = set()
    for top in dirs:
        for root, subdirs, files in os.walk(top):
            subdirs[:] = [d for d in subdirs if d not in SKIP and not d.startswith("build")]
            for f in files:
                if not f.endswith(".c"):
                    continue
                text = open(os.path.join(root, f), encoding="utf-8", errors="ignore").read()
                if "tdsh_board_" not in text:
                    continue
                keys.update(CALL.findall(text))
                for k in BUILT.findall(text):
                    if "%d" in k:
                        keys.add(k.replace("%d", "N"))
    return keys


def main(argv):
    if argv[:1] == ["--doc"]:
        page, listing = argv[1], argv[2]
        text = open(page, encoding="utf-8").read()
        missing = []
        for k in open(listing, encoding="utf-8").read().split():
            pattern = re.escape(k).replace("N", r"(?:\d|\*|N)")
            if not re.search(r"`" + pattern + r"`", text) and not re.search(
                    r"`" + re.escape(k.rsplit(".", 1)[0]) + r"\.\*`", text):
                missing.append(k)
        for k in missing:
            print("not described: " + k)
        return 1 if missing else 0
    record = "--record" in argv
    args = [a for a in argv if a != "--record"]
    if len(args) < 2:
        print(__doc__)
        return 2
    listing, dirs = args[0], args[1:]
    now = keys_in(dirs)
    if record:
        with open(listing, "w", encoding="utf-8", newline="\n") as f:
            f.write("\n".join(sorted(now)) + "\n")
        print("recorded %d keys in %s" % (len(now), listing))
        return 0
    old = set(open(listing, encoding="utf-8").read().split())
    gone, new = sorted(old - now), sorted(now - old)
    for k in gone:
        print("- %s (no longer read: 1.x boards may still set it)" % k)
    for k in new:
        print("+ %s (new: describe it, then --record)" % k)
    if gone or new:
        return 1
    print("board.conf keys match %s (%d keys)" % (listing, len(now)))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
