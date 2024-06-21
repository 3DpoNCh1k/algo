#!/usr/bin/env python3

import argparse
import json
import os
import re
import subprocess
import sys
import traceback

from pathlib import Path

from rithm.commands.clean import clean_command
from rithm.commands.prepare_submission import prepare_submission_command
from rithm.commands.run import run_command


def main():
    parser = argparse.ArgumentParser(prog="rithm")

    subparsers = parser.add_subparsers()

    run = subparsers.add_parser("run")
    run.add_argument("filename")
    run.add_argument("profile")
    run.add_argument("local_debug", nargs="?", default=False)
    run.add_argument("--compiler", choices=["g++", "clang"], default="g++")
    run.set_defaults(cmd=run_command)

    clean = subparsers.add_parser("clean")
    clean.add_argument("path")
    clean.set_defaults(cmd=clean_command)

    submission = subparsers.add_parser("prepare_submission")
    submission.add_argument("filename")
    submission.set_defaults(cmd=prepare_submission_command)

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
