import os
import subprocess
from typing import List

from consts import INSTANCES_PATH, PARAMS_DIR_PATH, EXEC_PATH, RUN_PARALLEL


def generate_files() -> List[str]:
    return [f"{INSTANCES_PATH}/i{i:02}.json" for i in range(25, 31)]


def get_param_files() -> List[str]:
    return [
        os.path.join(PARAMS_DIR_PATH, file)
        for file in os.listdir(PARAMS_DIR_PATH)
        if file.endswith(".json")
    ]


def run_problem_in_new_console(
    exec_path: str, instance_file: str, param_file: str
) -> None:
    print(f"Running {instance_file} with {exec_path} and params {param_file}")

    if RUN_PARALLEL:
        subprocess.Popen(
            [exec_path, instance_file, param_file],
            creationflags=subprocess.CREATE_NEW_CONSOLE,
        )
    else:
        subprocess.run(
            [exec_path, instance_file, param_file], capture_output=True, text=True
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


if __name__ == "__main__":
    main()
