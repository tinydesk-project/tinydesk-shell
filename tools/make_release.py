#!/usr/bin/env python3
"""make_release.py - package TinyDesk Shell for people without a toolchain.

Run it after building the three ESP-IDF projects (the repository root for the
ESP32-C6, projects/esp32 for the classic ESP32, projects/esp32s3 for the
ESP32-S3) and, optionally, the POSIX
host program. For each board it merges what `idf.py flash` writes (read
from <build>/flash_args) into one "factory" image, and writes the flat set
of files a GitHub release carries:

    dist/tinydesk-shell-<version>/
        tinydesk-shell-<version>-<board>-factory.bin   esptool, offset 0x0
        manifest-shell-<board>.json                   ESP Web Tools, one per board
        tinydesk-shell-linux-x86_64.tar.gz            with --host-linux
        tinydesk-shell-windows-x64.zip                with --host-windows
        SHA256SUMS.txt, README.txt

The names match the Shell edition files of a TinyDesk release, so the TinyDesk
web installer can use either.

    python tools/make_release.py [--build-dir build] [--host-linux build-host/tdsh_host]
                                 [--host-windows build-host/tdsh_host.exe] [--out dist]
                                 [--allow-board-conf]

Needs esptool (in the ESP-IDF Python environment; `pip install esptool`
otherwise).
"""
import argparse
import hashlib
import io
import json
import os
import shutil
import subprocess
import sys
import tarfile
import time
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TITLE = "TinyDesk Shell"
BOARDS = [
    # board id, project dir, esptool chip, ESP Web Tools chipFamily, what it needs
    ("esp32c6", ".", "esp32c6", "ESP32-C6", "ESP32-C6 with 8 MB flash"),
    ("esp32", "projects/esp32", "esp32", "ESP32", "any ESP32 with 4 MB flash or more (PSRAM optional)"),
    ("esp32s3", "projects/esp32s3", "esp32s3", "ESP32-S3", "any ESP32-S3 with 4 MB flash or more (Octal PSRAM optional)"),
]


def read_flash_args(build):
    """(esptool options, [(offset, path)]) from <build>/flash_args."""
    with open(os.path.join(build, "flash_args")) as f:
        lines = [l.strip() for l in f if l.strip()]
    parts = []
    for line in lines[1:]:
        off, path = line.split(None, 1)
        parts.append((int(off, 16), os.path.join(build, path)))
    return lines[0].split(), sorted(parts)


def project_version(build):
    with open(os.path.join(build, "project_description.json")) as f:
        return json.load(f)["project_version"]


def builtin_settings(build):
    """Keys set in the board configuration built into the firmware."""
    path = os.path.join(build, "esp-idf", "main", "board_builtin.conf")
    if not os.path.exists(path):
        return []
    keys = []
    with open(path, encoding="utf-8") as f:
        for line in f:
            line = line.split("#", 1)[0].strip()
            if "=" in line and line.split("=", 1)[1].strip():
                keys.append(line.split("=", 1)[0].strip())
    return keys


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(65536), b""):
            h.update(block)
    return h.hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--build-dir", default="build", help="build folder inside each project")
    ap.add_argument("--host-linux", help="the Linux host program (build-host/tdsh_host)")
    ap.add_argument("--host-windows", help="the Windows program (build-host/tdsh_host.exe, MinGW, static)")
    ap.add_argument("--out", default=os.path.join(ROOT, "dist"))
    ap.add_argument("--allow-board-conf", action="store_true",
                    help="package images built with a board.conf (private use only)")
    args = ap.parse_args()

    with open(os.path.join(ROOT, "VERSION")) as f:
        version = f.read().strip()
    builds = []
    for board, proj, chip, family, needs in BOARDS:
        build = os.path.normpath(os.path.join(ROOT, proj, args.build_dir))
        if not os.path.exists(os.path.join(build, "flash_args")):
            sys.exit("%s is not built (run idf.py build in %s)" % (board, os.path.normpath(os.path.join(ROOT, proj))))
        if project_version(build) != version:
            sys.exit("%s was built as %s, VERSION says %s: rebuild" % (board, project_version(build), version))
        # A private board.conf would publish your pins and drive them on other
        # people's boards.
        settings = builtin_settings(build)
        if settings and not args.allow_board_conf:
            sys.exit("%s was built with board settings (%s): remove %s/board.conf and rebuild, "
                     "or pass --allow-board-conf for a private image" % (board, ", ".join(settings[:3]), proj))
        builds.append((board, chip, family, needs, build))

    out = os.path.join(args.out, "tinydesk-shell-" + version)
    if os.path.exists(out):
        shutil.rmtree(out)
    os.makedirs(out)

    readme = ["%s %s" % (TITLE, version), "", "Flash at 0x0 with esptool, or use the TinyDesk web installer:"]
    for board, chip, family, needs, build in builds:
        opts, parts = read_flash_args(build)
        factory = "tinydesk-shell-%s-%s-factory.bin" % (version, board)
        cmd = [sys.executable, "-m", "esptool", "--chip", chip, "merge_bin", "-o", os.path.join(out, factory)] + opts
        for off, src in parts:
            cmd += ["0x%x" % off, src]
        subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL)
        manifest = {
            "name": "%s (%s)" % (TITLE, needs.split(" (")[0]),
            "version": version,
            "new_install_prompt_erase": True,
            "builds": [{"chipFamily": family, "parts": [{"path": "firmware/" + factory, "offset": 0}]}],
        }
        with open(os.path.join(out, "manifest-shell-%s.json" % board), "w") as f:
            json.dump(manifest, f, indent=2)
        readme += ["  %s: %s" % (board, needs), "    esptool.py --chip %s write_flash 0x0 %s" % (chip, factory)]
        print("%-8s %s" % (board, factory))

    readme += [
        "",
        "A factory image rewrites everything below the file system, NVS included,",
        "so users, Wi-Fi networks and the SSH host key start fresh.",
        "",
        "After installing: open the board's serial port in a terminal (UTF-8;",
        "115200 baud on the ESP32, any speed on the ESP32-C6's USB port) and press",
        "Enter. You start as root; the factory root password is TinyDesk. Change it",
        "locally with passwd before remote access. 'help' lists the commands.",
    ]

    if args.host_linux:
        if not os.path.exists(args.host_linux):
            sys.exit("no such program: %s" % args.host_linux)
        name = "tinydesk-shell-linux-x86_64"
        notes = ("%s %s for Linux (x86_64)\n\n  ./tdsh\n\n"
                 "Its files live in ~/.local/share/tdsh/rootfs (your real home is not used).\n"
                 "Type 'help' for the commands, 'exit' to leave.\n" % (TITLE, version)).encode()
        path = os.path.join(out, name + ".tar.gz")
        with tarfile.open(path, "w:gz") as t:
            info = t.gettarinfo(args.host_linux, name + "/tdsh")
            info.mode = 0o755
            with open(args.host_linux, "rb") as f:
                t.addfile(info, f)
            ti = tarfile.TarInfo(name + "/README.txt")
            ti.size, ti.mode, ti.mtime = len(notes), 0o644, int(time.time())
            t.addfile(ti, io.BytesIO(notes))
            t.add(os.path.join(ROOT, "LICENSE"), name + "/LICENSE")
        readme += ["", "PC program: %s.tar.gz (README.txt inside)." % name]
        print("host     %s.tar.gz" % name)

    if args.host_windows:
        if not os.path.exists(args.host_windows):
            sys.exit("no such program: %s" % args.host_windows)
        name = "tinydesk-shell-windows-x64"
        notes = ("%s %s for Windows (x64)\r\n\r\n"
                 "Start tdsh.exe in Windows Terminal (or any console window):\r\n\r\n"
                 "  .\\tdsh.exe\r\n\r\n"
                 "Its files live in %%LOCALAPPDATA%%\\tdsh\\rootfs (your real files are not used).\r\n"
                 "Type 'help' for the commands, 'exit' to leave.\r\n" % (TITLE, version))
        path = os.path.join(out, name + ".zip")
        with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED) as z:
            z.write(args.host_windows, name + "/tdsh.exe")
            z.writestr(name + "/README.txt", notes)
            z.write(os.path.join(ROOT, "LICENSE"), name + "/LICENSE")
        readme += ["", "PC program: %s.zip (README.txt inside)." % name]
        print("host     %s.zip" % name)

    with open(os.path.join(out, "README.txt"), "w") as f:
        f.write("\n".join(readme) + "\n")
    sums = ["%s  %s" % (sha256(os.path.join(out, n)), n) for n in sorted(os.listdir(out))]
    with open(os.path.join(out, "SHA256SUMS.txt"), "w") as f:
        f.write("\n".join(sums) + "\n")
    print("release in %s" % out)


if __name__ == "__main__":
    main()
