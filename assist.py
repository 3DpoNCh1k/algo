#!/usr/bin/env python3

import argparse
import json
import os
import subprocess
import sys
import traceback


def load_config():
    return json.load(open("config.json"))


def run_command(args):
    filename = args.filename
    profile = args.profile
    dbg = bool(args.local_debug)
    compiler = args.compiler

    assert filename[-4:] == ".cpp"
    executable = filename[:-4] + ".exe"

    config = load_config()
    config = config["compiler"][compiler]
    std = config["std"]
    always_flags = config["always"]
    profile_flags = config["profiles"][profile]
    debug_flags = config["localDebug"] if dbg else ""

    cmd = f"{compiler} --std={std} {always_flags} {profile_flags} {debug_flags}"
    cmd += f" -o {executable} {filename}"

    if os.path.exists(executable):
        os.remove(executable)

    res = subprocess.run(cmd, shell=True, check=True)
    assert res.returncode == 0
    res = subprocess.run(executable, shell=True, check=True)
    assert res.returncode == 0


def main():
    parser = argparse.ArgumentParser(prog="Assistant")

    subparsers = parser.add_subparsers()

    run = subparsers.add_parser("run")
    run.add_argument("filename")
    run.add_argument("profile")
    run.add_argument("local_debug", nargs="?", default=False)
    run.add_argument("--compiler", choices=["g++", "clang"], default="g++")
    run.set_defaults(cmd=run_command)

    args = parser.parse_args()
    if "cmd" not in args:
        parser.print_help()
        sys.exit(2)

    try:
        args.cmd(args)
    except Exception as e:
        print(e)
        traceback.print_exc()
        sys.exit(1)


if __name__ == "__main__":
    main()
