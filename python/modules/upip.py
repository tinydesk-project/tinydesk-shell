# upip: install MicroPython packages for py (from ushell's upip).
#
#   upip install PKG [PKG...]        from micropython.org's index (mip), a
#   upip install -r FILE                github:/gitlab: path or a URL;
#                                       PKG@VERSION for a version
#   upip uninstall PKG [PKG...]      remove exactly the files PKG installed
#   upip uninstall -r FILE
#   upip list                        what is installed here
#   upip freeze [FILE]               the packages as a requirements file
#
# Where: the active virtual environment's lib (`activate DIR`), otherwise
# the user's ~/lib (/lib for root). Each place keeps a record of the files
# every package added -- venv.json in an environment, .upip.json in a lib
# -- so uninstall removes those and nothing else. Run it from the shell as
# `upip ...` (the command runs this module in py).
import json
import os
import sys

import tdsh


def _isdir(path):
    try:
        return os.stat(path)[0] & 0x4000 != 0
    except OSError:
        return False


def _exists(path):
    try:
        os.stat(path)
        return True
    except OSError:
        return False


def place():
    """(lib directory, record file, environment name or None)."""
    env = tdsh.getvar("VIRTUAL_ENV")
    if env:
        return env + "/lib", env + "/venv.json", env.rsplit("/", 1)[-1]
    lib = "/lib" if tdsh.user() == "root" else tdsh.home() + "/lib"
    return lib, lib + "/.upip.json", None


def _load(record):
    try:
        with open(record) as f:
            data = json.load(f)
    except (OSError, ValueError):
        data = {}
    data.setdefault("packages", {})
    return data


def _save(record, data):
    with open(record, "w") as f:
        json.dump(data, f)


def _files(top):
    """Every file under top, as paths relative to it."""
    out = []

    def walk(rel):
        here = top + ("/" + rel if rel else "")
        for name in os.listdir(here):
            sub = rel + "/" + name if rel else name
            if _isdir(here + "/" + name):
                walk(sub)
            else:
                out.append(sub)

    if _isdir(top):
        walk("")
    return set(out)


def _requirements(path):
    with open(path) as f:
        return [l.split("#")[0].strip() for l in f if l.split("#")[0].strip()]


def _names(args):
    if args[:1] == ["-r"]:
        if len(args) != 2:
            raise ValueError("-r takes one file")
        return _requirements(args[1])
    return args


def install(packages):
    import mip

    lib, record, _ = place()
    if not _isdir(lib):
        os.mkdir(lib)
    data = _load(record)
    ok = True
    for spec in packages:
        name, _, version = spec.partition("@")
        before = _files(lib)
        # mip makes every folder of its target from the top; a user may not
        # look at /home itself, so give it the target relative to the cwd.
        cwd = os.getcwd()
        os.chdir(lib)
        try:
            mip.install(name, target=".", version=version or None)
        finally:
            os.chdir(cwd)
        added = sorted(_files(lib) - before)
        if not added:
            print("upip: %s installed no files" % spec)
            ok = False
            continue
        old = data["packages"].get(name, {}).get("files", [])
        data["packages"][name] = {"version": version or "latest", "files": sorted(set(old) | set(added))}
        _save(record, data)
    return 0 if ok else 1


def uninstall(packages):
    lib, record, _ = place()
    data = _load(record)
    ok = True
    for name in packages:
        name = name.partition("@")[0]
        entry = data["packages"].pop(name, None)
        if entry is None:
            print("upip: %s is not installed here (upip list)" % name)
            ok = False
            continue
        dirs = set()
        for rel in entry["files"]:
            try:
                os.remove(lib + "/" + rel)
            except OSError:
                pass
            while "/" in rel:
                rel = rel.rsplit("/", 1)[0]
                dirs.add(rel)
        for d in sorted(dirs, key=len, reverse=True):   # empty package folders
            try:
                os.rmdir(lib + "/" + d)
            except OSError:
                pass
        print("Removed %s (%d files)" % (name, len(entry["files"])))
    _save(record, data)
    return 0 if ok else 1


def listing():
    lib, record, env = place()
    data = _load(record)
    print("%s (%s):" % (lib, "environment " + env if env else "no environment active"))
    if not data["packages"]:
        print("  nothing installed")
    for name in sorted(data["packages"]):
        p = data["packages"][name]
        print("  %-24s %-8s %d files" % (name, p["version"], len(p["files"])))
    return 0


def freeze(out=None):
    data = _load(place()[1])
    lines = [n if p["version"] == "latest" else n + "@" + p["version"]
             for n, p in sorted(data["packages"].items())]
    if out:
        with open(out, "w") as f:
            f.write("\n".join(lines) + ("\n" if lines else ""))
    else:
        for l in lines:
            print(l)
    return 0


USAGE = """usage: upip install PKG[@VERSION]... | install -r FILE
       upip uninstall PKG... | uninstall -r FILE
       upip list
       upip freeze [FILE]
Packages go to the active virtual environment (activate DIR), else ~/lib."""


def main(argv=None):
    args = list(sys.argv[1:] if argv is None else argv)
    if not args or args[0] in ("-h", "--help", "help"):
        print(USAGE)
        return 0 if args else 2
    cmd, rest = args[0], args[1:]
    try:
        if cmd == "install" and rest:
            return install(_names(rest))
        if cmd == "uninstall" and rest:
            return uninstall(_names(rest))
        if cmd == "list" and not rest:
            return listing()
        if cmd == "freeze" and len(rest) <= 1:
            return freeze(rest[0] if rest else None)
    except (OSError, ValueError) as e:
        print("upip:", e)
        return 1
    print(USAGE)
    return 2
