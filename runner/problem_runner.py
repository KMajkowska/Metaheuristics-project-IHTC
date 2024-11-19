import os
import subprocess
from typing import List
import winsound

EXEC_PATH: str = "../IHTC-2024/x64/Release/IHTC-2024.exe"
PARAMS_PATH: str = "../IHTC-2024/params.json"

INSTANCES_PATH: str = "../datasets/competition_instances"

FREQUENCY: int = 2500
DURATION: int = 1000


def generate_files() -> List[str]:
    return [f"{INSTANCES_PATH}/i{i:02}.json" for i in range(1, 11)]


def main() -> None:
    if not os.path.exists(EXEC_PATH):
        raise Exception(f"Executable not found: {EXEC_PATH}")

    for file_path in generate_files():
        if not os.path.exists(file_path):
            raise Exception(f"File path not found: {file_path}")

        print(f"Running {EXEC_PATH} with {file_path}")

        result = subprocess.run([EXEC_PATH, file_path, PARAMS_PATH], capture_output=True, text=True)

        print("Output:")
        print(result.stdout)

        if result.stderr:
            print("Errors:")
            print(result.stderr)


if __name__ == "__main__":
    main()

    winsound.Beep(FREQUENCY, DURATION)
