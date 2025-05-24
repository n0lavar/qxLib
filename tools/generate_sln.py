
import os
import shutil
import subprocess
import argparse
import sys
from pathlib import Path
from typing import List


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


def run_cmake(cpp_compiler_flags: str, cmake_flags: str, sources_folder: Path, build_folder: Path, cmake_generator: str, arch: str) -> int:
    cmake_command: List[str] = [
        "cmake",
        cmake_flags,
        f"-DCMAKE_CXX_FLAGS={cpp_compiler_flags}",
        "-S", sources_folder,
        "-B", build_folder,
        "-G", cmake_generator,
        "-A", arch
    ]

    cmake_command = [arg for arg in cmake_command if arg.strip()]
    result = subprocess.run(cmake_command, shell=True)

    return result.returncode


def create_parser():
    parser = argparse.ArgumentParser(conflict_handler='resolve')
    parser.add_argument("--sources_folder", default="..")
    parser.add_argument("--build_folder", default="../build")
    parser.add_argument("--cmake_generator", default="Visual Studio 17 2022")
    parser.add_argument("--arch", default="x64")
    parser.add_argument("--cmake_flags", default="-DGENERATE_TESTS=1")
    parser.add_argument("--cpp_compiler_flags", default="")
    return parser


def main(args) -> int:
    sources_folder: Path = os.path.abspath(args.sources_folder)
    build_folder: Path = os.path.abspath(args.build_folder)

    os.makedirs(name=build_folder, exist_ok=True)
    clean_build_folder(build_folder)

    return run_cmake(
        cpp_compiler_flags=args.cpp_compiler_flags,
        cmake_flags=args.cmake_flags,
        sources_folder=sources_folder,
        build_folder=build_folder,
        cmake_generator=args.cmake_generator,
        arch=args.arch
    )


if __name__ == "__main__":
    args = create_parser().parse_args()
    sys.exit(main(args))
