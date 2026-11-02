
import os
import shutil
import subprocess
import argparse
import sys
from pathlib import Path
from typing import List, Optional


def clean_build_folder(build_folder: Path):

    ALLOWED_EXTENSIONS: List[str] = [x.lower()
                                     for x in [".DotSettings", ".DotSettings.user"]]

    for entry in os.listdir(build_folder):
        full_path: Path = os.path.join(build_folder, entry)

        if os.path.isfile(full_path):
            _, extension = os.path.splitext(entry)
            if extension.lower() not in ALLOWED_EXTENSIONS:
                os.remove(full_path)
        elif os.path.isdir(full_path):
            shutil.rmtree(full_path, ignore_errors=True)


def run_cmake(cpp_compiler_flags: str,
              cmake_flags: str,
              sources_folder: Path,
              build_folder: Path,
              cmake_generator: str,
              arch: str,
              toolchain_file: Optional[str],
              tests: bool,
              tests_debug_breaks: bool,
              benchmarks: bool
              ) -> int:

    cmake_flags += " -DQX_GENERATE_TESTS=" + ("1" if tests else "0")
    cmake_flags += " -DTEST_DEBUG_BREAKS=" + ("1" if tests_debug_breaks else "0")
    cmake_flags += " -DGENERATE_BENCHMARKS=" + ("1" if benchmarks else "0")

    cmake_command: List[str] = [
        "cmake",
        *cmake_flags.split(),
        f"-DCMAKE_CXX_FLAGS={cpp_compiler_flags}",
        "-S", sources_folder,
        "-B", build_folder,
        "-G", cmake_generator,
        "-A", arch
    ]

    if toolchain_file:
        cmake_command.append(f"-DCMAKE_TOOLCHAIN_FILE={toolchain_file}")

    cmake_command = [arg for arg in cmake_command if arg.strip()]
    result = subprocess.run(cmake_command, shell=True)

    return result.returncode


def create_parser():
    parser = argparse.ArgumentParser(conflict_handler='resolve')
    parser.add_argument("--sources_folder", default="..")
    parser.add_argument("--build_folder", default="../build/msvc")
    parser.add_argument("--toolchain_file", help="Path to a CMake toolchain file")
    parser.add_argument("--cmake_generator", default="Visual Studio 17 2022")
    parser.add_argument("--arch", default="x64")
    parser.add_argument("--tests", action=argparse.BooleanOptionalAction)
    parser.add_argument("--tests_debug_breaks", action=argparse.BooleanOptionalAction)
    parser.add_argument("--benchmarks", action=argparse.BooleanOptionalAction)
    parser.add_argument("--cmake_flags", default="")
    parser.add_argument("--cpp_compiler_flags", default="")
    return parser


def main(args) -> int:
    sources_folder: Path = os.path.abspath(args.sources_folder)
    build_folder: Path = os.path.abspath(args.build_folder)
    toolchain_file: str | None = os.path.abspath(args.toolchain_file) if args.toolchain_file else None

    os.makedirs(name=build_folder, exist_ok=True)
    clean_build_folder(build_folder)

    return run_cmake(
        cpp_compiler_flags=args.cpp_compiler_flags,
        cmake_flags=args.cmake_flags,
        sources_folder=sources_folder,
        build_folder=build_folder,
        cmake_generator=args.cmake_generator,
        arch=args.arch,
        toolchain_file=toolchain_file,
        tests=args.tests,
        tests_debug_breaks=args.tests_debug_breaks,
        benchmarks=args.benchmarks
    )


if __name__ == "__main__":
    args = create_parser().parse_args()
    sys.exit(main(args))
