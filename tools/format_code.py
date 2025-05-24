import argparse
import concurrent.futures
import fnmatch
import os
import shutil
import subprocess
import sys
import time
from pathlib import Path
from typing import List

CLANG_FORMAT_EXE = "clang-format"
CPP_EXTENSIONS = ["h", "cpp", "inl"]


def is_debugger_active() -> bool:
    return hasattr(sys, 'gettrace') and sys.gettrace() is not None


def get_root_dir() -> str:
    result: subprocess.CompletedProcess = subprocess.run(
        "git rev-parse --show-toplevel",
        capture_output=True,
        shell=True)

    return result.stdout.decode().strip()


def update_progressbar(start_time, progressbar_size, total_iterations, current_iteration, prefix):
    x = int(progressbar_size * current_iteration / total_iterations)
    remaining = ((time.time() - start_time) / current_iteration) * \
        (total_iterations - current_iteration)

    mins, sec = divmod(remaining, 60)
    time_str = f"{int(mins):02}:{sec:05.2f}"

    print(f"{prefix}[{u'█'*x}{('.'*(progressbar_size-x))}] {current_iteration} / {total_iterations} Estimate: {time_str}", end='\r', flush=True)


def format_files(changed_files: List[Path]) -> int:
    changed_cpp_files: List[Path] = []
    for file in changed_files:
        if any(fnmatch.fnmatch(file, "*." + extension) for extension in CPP_EXTENSIONS):
            changed_cpp_files.append(file)

    if len(changed_cpp_files) == 0:
        print("There is nothing to format, great!")
        return 0

    if not shutil.which(CLANG_FORMAT_EXE):
        print("Can't find installed clang-format.")
        return 1

    start_time = time.time()
    num_formatted_files = 0
    num_skipped_files = 0

    def format_file(file: Path):
        nonlocal num_formatted_files, num_skipped_files

        run_result = subprocess.run(
            [CLANG_FORMAT_EXE, "--dry-run", "--Werror", "--ferror-limit=1", file], stderr=subprocess.DEVNULL)
        if run_result.returncode != 0:
            subprocess.run([CLANG_FORMAT_EXE, "-i", file])
            num_formatted_files += 1
        else:
            num_skipped_files += 1

        update_progressbar(start_time, 60, len(
            changed_cpp_files), num_formatted_files + num_skipped_files, "Formatting... ")

    with concurrent.futures.ThreadPoolExecutor() as executor:
        for file in changed_cpp_files:
            executor.submit(format_file, file)

        executor.shutdown()
        print(
            f"\nDone! Time: {time.time() - start_time:.2f}s, number of formatted files: {num_formatted_files}, number of skipped files: {num_skipped_files}")

    return 0


def format_all_files() -> int:
    code_root_dir = get_root_dir()
    print(
        f"The script is about to format all files in directory {code_root_dir}")
    paths: List[Path] = []
    for path, _, files in os.walk(code_root_dir):
        for file in files:
            paths.append(os.path.join(path, file))

    return format_files(paths)


def main(args) -> int:
    if args.silent:
        sys.stdout = open(os.devnull, 'w')

    return format_all_files()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--silent",
                        action=argparse.BooleanOptionalAction,
                        default=False)
    
    sys.exit(main(parser.parse_args()))
