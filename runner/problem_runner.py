import os
import subprocess
from typing import List
import winsound

EXEC_PATH: str = "../IHTC-2024/x64/Release/IHTC-2024.exe"
PARAMS_DIR: str = "./params"
INSTANCES_PATH: str = "../datasets/ihtc2024_test_dataset"

FREQUENCY: int = 2500
DURATION: int = 1000


def beep() -> None:
    winsound.Beep(FREQUENCY, DURATION)


def generate_files() -> List[str]:
    return [f"{INSTANCES_PATH}/test{i:02}.json" for i in range(1, 6)]


def get_param_files() -> List[str]:
    return [
        os.path.join(PARAMS_DIR, file)
        for file in os.listdir(PARAMS_DIR)
        if file.endswith(".json")
    ]


def run_problem_in_new_console(
    exec_path: str, instance_file: str, param_file: str
) -> None:
    print(f"Running {instance_file} with {exec_path} and params {param_file}")

    subprocess.Popen(
        ["cmd.exe", "/c", "start", "", exec_path, instance_file, param_file],
        creationflags=subprocess.CREATE_NEW_CONSOLE,
    )


def run_all_problems(exec_path: str) -> None:
    instance_files = generate_files()
    param_files = get_param_files()

    for param_file in param_files:
        full_param_path = os.path.abspath(param_file)

        if not os.path.exists(full_param_path):
            raise Exception(f"Parameter file not found: {full_param_path}")

        for instance_file in instance_files:
            full_instance_path = os.path.abspath(instance_file)

            if not os.path.exists(full_instance_path):
                raise Exception(f"Instance file not found: {full_instance_path}")

            run_problem_in_new_console(exec_path, full_instance_path, full_param_path)


def main() -> None:
    full_exec_path = os.path.abspath(EXEC_PATH)

    if not os.path.exists(full_exec_path):
        raise Exception(f"Executable not found: {full_exec_path}")

    run_all_problems(full_exec_path)

    # beep()


if __name__ == "__main__":
    main()
