"""check_py_contract.py - py's modules against python/py_contract.json.

    python tools/check_py_contract.py PROGRAM            check (exit 1 on a difference)
    python tools/check_py_contract.py --record PROGRAM   write the contract

PROGRAM is the PC shell (tdsh_host) or a program embedding it. The tool
runs `py` in it and lists every public name of the modules below, and the
public members of their classes. Names may be added within 1.x (record
them); a name that disappears breaks scripts written for 1.x, so the check
fails until it is restored or 2.0 comes (see STABILITY.md).
"""
import json
import os
import subprocess
import sys
import tempfile

MODULES = [
    "tdsh", "network", "socket", "ssl", "machine", "neopixel", "websocket",
    "requests", "umqtt.simple", "umqtt.robust", "aiohttp", "upip", "mip",
]
HERE = os.path.dirname(os.path.abspath(__file__))
CONTRACT = os.path.join(HERE, "..", "python", "py_contract.json")

# One line, no double quotes and no $: the shell passes it to py -c as is.
SCRIPT = (
    "import json;M=%s;"
    "pub=lambda o:sorted(n for n in dir(o) if n[0]!='_');"
    "mod=lambda m:__import__(m,None,None,['_']);"
    "cls=lambda o:{n:pub(getattr(o,n)) for n in pub(o) if isinstance(getattr(o,n),type)};"
    "print('JSON:'+json.dumps({m:{'names':pub(mod(m)),'classes':cls(mod(m))} for m in M}))"
) % repr(MODULES).replace('"', "'")


def collect(program):
    with tempfile.TemporaryDirectory() as tmp:
        env = dict(os.environ, LOCALAPPDATA=tmp, HOME=tmp, XDG_DATA_HOME=tmp)
        cmd = 'py -c "%s"\nexit\n' % SCRIPT
        res = subprocess.run([program], input=cmd.encode(), capture_output=True, env=env, timeout=120)
    out = res.stdout.decode("utf-8", "replace")
    for line in out.splitlines():
        if line.startswith("JSON:"):
            return json.loads(line[5:])
    print(out[-2000:])
    raise SystemExit("py did not answer (see the output above)")


def main(argv):
    record = "--record" in argv
    args = [a for a in argv if a != "--record"]
    if len(args) != 1:
        print(__doc__)
        return 2
    now = collect(args[0])
    if record:
        with open(CONTRACT, "w", encoding="utf-8", newline="\n") as f:
            json.dump({"contract": "tdsh-py", "policy": "Within 1.x names are only added; "
                       "none is removed or changes meaning (STABILITY.md).", "modules": now},
                      f, indent=1, sort_keys=True)
            f.write("\n")
        print("recorded %d modules in %s" % (len(now), CONTRACT))
        return 0
    old = json.load(open(CONTRACT, encoding="utf-8"))["modules"]
    missing, added = [], []
    for m in sorted(set(old) | set(now)):
        o, n = old.get(m), now.get(m)
        if o is None:
            added.append(m)
            continue
        if n is None:
            missing.append(m)
            continue
        for name in o["names"]:
            if name not in n["names"]:
                missing.append("%s.%s" % (m, name))
        for name in n["names"]:
            if name not in o["names"]:
                added.append("%s.%s" % (m, name))
        for c, members in o["classes"].items():
            for name in members:
                if name not in n["classes"].get(c, []):
                    missing.append("%s.%s.%s" % (m, c, name))
        for c, members in n["classes"].items():
            for name in members:
                if name not in o["classes"].get(c, []):
                    added.append("%s.%s.%s" % (m, c, name))
    for x in missing:
        print("- " + x)
    for x in added:
        print("+ " + x)
    if missing or added:
        print("py's modules differ from python/py_contract.json.")
        print("A missing name breaks 1.x scripts; new ones: tools/check_py_contract.py --record PROGRAM")
        return 1
    print("py's modules match the contract (%d modules)" % len(now))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
