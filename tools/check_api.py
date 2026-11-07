"""check_api.py - the public C API against its recorded snapshot.

    python tools/check_api.py SNAPSHOT HEADER...            check (exit 1 on a difference)
    python tools/check_api.py --record SNAPSHOT HEADER...   write the snapshot

Every declaration in the public headers (functions, types, structs and
enums with their members, macros with their values) becomes one normalised
line; comments, blank lines, include guards and #include lines do not count.
The snapshot is committed, so a change to the public API fails the tests
until it is recorded on purpose, and the diff shows exactly what changed.
Within a major version a recorded change may only add (see STABILITY.md).
"""
import os
import re
import sys


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


def declarations(path):
    """The header's declarations, one normalised string each."""
    text = strip_comments(open(path, encoding="utf-8").read())
    text = re.sub(r"\\\n", " ", text)            # macro continuation lines
    name = os.path.basename(path)
    out = []
    code = []
    for line in text.split("\n"):
        s = line.strip()
        if s.startswith("#"):
            m = re.match(r"#\s*define\s+(\w+)(\([^)]*\))?\s*(.*)", s)
            # Include guards and version numbers (they change every release;
            # version_errors() checks them) are not API.
            if m and not re.search(r"(_H_?|_VERSION(_MAJOR|_MINOR|_PATCH)?)$", m.group(1)):
                out.append("#define %s%s %s" % (m.group(1), m.group(2) or "",
                                                 " ".join(m.group(3).split())))
            continue
        code.append(s)
    body = " ".join(code)
    body = re.sub(r'extern\s+"C"\s*\{', " ", body)
    # Top-level statements: split on ';' at brace depth 0.
    depth, cur = 0, []
    for ch in body:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth < 0:        # the closing brace of extern "C"
                depth = 0
                continue
        if ch == ";" and depth == 0:
            stmt = " ".join("".join(cur).split())
            if stmt:
                out.append(stmt + ";")
            cur = []
        else:
            cur.append(ch)
    rest = " ".join("".join(cur).split())
    if rest:
        out.append(rest)
    return ["%s: %s" % (name, d) for d in out]


def version_errors(headers):
    """X_VERSION "a.b.c" must agree with X_VERSION_MAJOR/_MINOR/_PATCH."""
    errors = []
    for h in headers:
        text = open(h, encoding="utf-8").read()
        for m in re.finditer(r'#define\s+(\w+)_VERSION\s+"(\d+)\.(\d+)\.(\d+)"', text):
            pre = m.group(1)
            for part, want in zip(("MAJOR", "MINOR", "PATCH"), m.groups()[1:]):
                n = re.search(r"#define\s+%s_VERSION_%s\s+(\d+)" % (pre, part), text)
                if n and n.group(1) != want:
                    errors.append("%s: %s_VERSION_%s is %s, %s_VERSION says %s"
                                  % (os.path.basename(h), pre, part, n.group(1), pre, want))
    return errors


def main(argv):
    record = "--record" in argv
    args = [a for a in argv if a != "--record"]
    if len(args) < 2:
        print(__doc__)
        return 2
    snapshot, headers = args[0], args[1:]
    errors = version_errors(headers)
    for e in errors:
        print(e)
    if errors:
        return 1
    lines = []
    for h in sorted(headers, key=os.path.basename):
        lines += declarations(h)
    text = "\n".join(lines) + "\n"
    if record:
        with open(snapshot, "w", encoding="utf-8", newline="\n") as f:
            f.write(text)
        print("recorded %d declarations in %s" % (len(lines), snapshot))
        return 0
    try:
        old = open(snapshot, encoding="utf-8").read().splitlines()
    except FileNotFoundError:
        print("no snapshot %s: run with --record" % snapshot)
        return 1
    new = set(lines)
    removed = [l for l in old if l not in new]
    added = [l for l in lines if l not in set(old)]
    if not removed and not added:
        print("public API unchanged (%d declarations)" % len(lines))
        return 0
    for l in removed:
        print("- " + l)
    for l in added:
        print("+ " + l)
    print("The public API differs from %s." % snapshot)
    print("Removed or changed lines break 1.x users; added ones need a minor version.")
    print("If the change is meant: python tools/check_api.py --record SNAPSHOT HEADER...")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
