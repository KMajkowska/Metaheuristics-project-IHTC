import os
import subprocess
from typing import List
import winsound

EXEC_PATH: str = "../IHTC-2024/x64/Release/IHTC-2024.exe"
PARAMS_PATH: str = "./params/18.json"

INSTANCES_PATH: str = "../datasets/ihtc2024_test_dataset"

FREQUENCY: int = 2500
DURATION: int = 1000


def beep() -> None:
    winsound.Beep(FREQUENCY, DURATION)


def generate_files() -> List[str]:
    return [f"{INSTANCES_PATH}/test{i:02}.json" for i in range(1, 11)]

def run_problem(full_exec_path: str, file_path: str) -> None
    print(f"Running {full_exec_path} with \n {file_path}")

    result = subprocess.run(
        [EXEC_PATH, file_path, PARAMS_PATH], capture_output=True, text=True
    )

    print("Output:")
    print(result.stdout)

    if result.stderr:
        print("Errors:")
        print(result.stderr)


def run_all_problems(exec_path: str) -> None:
    for file_path in generate_files():
        full_file_file_path = os.path.abspath(file_path)

        if not os.path.exists(full_file_file_path):
            raise Exception(f"File path not found: {full_file_file_path}")

        run_problem(exec_path, full_file_file_path)

def main() -> None:
    full_exec_path = os.path.abspath(EXEC_PATH)

    if not os.path.exists(full_exec_path):
        raise Exception(f"Executable not found: {full_exec_path}")

    run_all_problems(full_exec_path)

    beep()


if __name__ == "__main__":
    main()
