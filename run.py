#!/usr/bin/env python3
import argparse
import subprocess
import sys
import tempfile
import traceback
import os
from pathlib import Path

CURRENT_FILE = Path(os.path.realpath(__file__))
CURRENT_DIRECTORY = CURRENT_FILE.parent
ALGO_PATH = Path(os.environ["ALGO_PATH"])

assert CURRENT_DIRECTORY == ALGO_PATH

DEFAULT_COVERAGE_PRESET="g++-debug-coverage"
DEFAULT_BUILD_PRESET="g++-debug"

def run_shell_cmd(cmd):
    result = subprocess.run(
        cmd, check=False, shell=True, capture_output=True, text=True
    )
    if result.returncode != 0:
        raise Exception(f"{cmd} failed:\n{result.stdout}\n{result.stderr}")


def cpp_files_recursive_iterator(directory: Path):
    extensions = [".cpp", ".hpp"]
    iterator = directory.glob("**/*")
    iterator = filter(lambda path: path.is_file(), iterator)
    iterator = filter(lambda file: file.suffix in extensions, iterator)
    return iterator


class CMake:
    def __init__(self):
        self.cmake = "cmake"
        run_shell_cmd(f"{self.cmake} --version")

    def configure(self, preset: str):
        run_shell_cmd(f"{self.cmake} --preset {preset}")

    def build(self, preset: str):
        run_shell_cmd(f"{self.cmake} --build --preset {preset}")


class CTest:
    def __init__(self):
        self.ctest = "ctest"
        run_shell_cmd(f"{self.ctest} --version")

    def test(self, preset: str):
        run_shell_cmd(f"{self.ctest} --preset {preset}")


class Coverage:
    def __init__(self):
        self.lcov = "lcov"
        run_shell_cmd(f"{self.lcov} --version")
        self.genhtml = "genhtml"
        run_shell_cmd(f"{self.genhtml} --version")

    def run(self, directory: Path, include_pattern: str, output_directory: Path):
        with tempfile.NamedTemporaryFile() as output_coverage_file:
            run_shell_cmd(
                f"{self.lcov} --directory {directory}  --include {include_pattern} --capture --output-file {output_coverage_file.name}"
            )
            run_shell_cmd(
                f"{self.genhtml} --demangle-cpp -o {output_directory} {output_coverage_file.name}"
            )


class ClangTidy:
    def __init__(self):
        self.clang_tidy = "clang-tidy"
        run_shell_cmd(f"{self.clang_tidy} --version")

    def run(self, file: Path, build_path: Path):
        run_shell_cmd(
            f"{self.clang_tidy} -p {build_path} --config-file=.clang-tidy {file}"
        )


class ClangFormat:
    def __init__(self):
        self.clang_format = "clang-format"
        run_shell_cmd(f"{self.clang_format} --version")

    def run(self, file: Path):
        run_shell_cmd(f"{self.clang_format} --style=file -i {file}")


def build(args):
    cmake = CMake()
    cmake.configure(args.preset)
    cmake.build(args.preset)


def test(args):
    ctest = CTest()
    ctest.test(args.preset)


def coverage(args):
    preset = DEFAULT_COVERAGE_PRESET
    # build
    cmake = CMake()
    cmake.configure(preset)
    cmake.build(preset)
    # run
    ctest = CTest()
    ctest.test(preset)
    # process
    coverage = Coverage()
    coverage.run(
        directory=ALGO_PATH / "build" / preset,
        include_pattern=f"{ALGO_PATH}/algo/*",
        output_directory=ALGO_PATH / "coverage",
    )


def format(args):
    path = Path(args.path)
    clang_format = ClangFormat()
    for file in [path] if path.is_file() else cpp_files_recursive_iterator(path):
        clang_format.run(file)


def lint(args):
    path = Path(args.path)
    preset = DEFAULT_BUILD_PRESET
    # lint
    clang_tidy = ClangTidy()
    for file in [path] if path.is_file() else cpp_files_recursive_iterator(path):
        clang_tidy.run(file=file, build_path=ALGO_PATH / "build" / preset)


def main():
    parser = argparse.ArgumentParser(prog="run")
    subparsers = parser.add_subparsers()

    run = subparsers.add_parser("build")
    run.add_argument("preset")
    run.set_defaults(cmd=build)

    run = subparsers.add_parser("test")
    run.add_argument("preset")
    run.set_defaults(cmd=test)

    run = subparsers.add_parser("coverage")
    run.set_defaults(cmd=coverage)

    run = subparsers.add_parser("format")
    run.add_argument("path")
    run.set_defaults(cmd=format)

    run = subparsers.add_parser("lint")
    run.add_argument("path")
    run.set_defaults(cmd=lint)

    args = parser.parse_args()

    if "cmd" not in args:
        parser.print_help()
        sys.exit(2)

    try:
        args.cmd(args)
    except Exception:
        traceback.print_exc()
        sys.exit(1)


if __name__ == "__main__":
    main()
