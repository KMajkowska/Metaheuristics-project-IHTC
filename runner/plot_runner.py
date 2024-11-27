import os

import pandas as pd
import matplotlib.pyplot as plt

LOG_FILES_PATH: str = "./log_files/"
PLOT_OUTPUT_PATH: str = "./plot_files/"

CURRENT_COL_NAME: str = "res"
BEST_COL_NAME: str = "resBest"
TEMP_COL_NAME: str = "actualTemp"
BEST_NEIGHBOUR: str = "bestNeighbour"
WORST_NEIGHBOUR: str = "worstNeighbour"
AVG_NEIGHBOUR: str = "avgNeighbour"
STD_DEV_NEIGHBOUR: str = "stdDevNeighbour"

CURR_MUTATOR: str = "currMutator"
SPLIT: int = 5

DPI: int = 100
FILE_FORMAT: str = "png"


def run_plot(csv_file_path: str, output_plot_path: str) -> pd.DataFrame:
    data = pd.read_csv(csv_file_path)

    min_value = min(
        data[CURRENT_COL_NAME].min(),
        data[BEST_COL_NAME].min(),
        data[WORST_NEIGHBOUR].min(),
        data[BEST_NEIGHBOUR].min(),
    )
    max_value = max(
        data[CURRENT_COL_NAME].max(),
        data[BEST_COL_NAME].max(),
        data[WORST_NEIGHBOUR].max(),
        data[BEST_NEIGHBOUR].max(),
    )

    plt.figure(figsize=(30, 15))

    plt.plot(data[WORST_NEIGHBOUR], label="Worst neighbour", color="red")

    plt.plot(data[CURRENT_COL_NAME], label="Current", color="blue")
    plt.plot(data[BEST_COL_NAME], label="Best", color="green")

    plt.plot(data[AVG_NEIGHBOUR], label="Avg neighbour", color="pink")

    plt.ylim(min_value, max_value)

    plt.xlabel("Iteration")
    plt.ylabel("Fitness")
    plt.title(f"Simulated Annealing (Min = {min_value}, Max = {max_value})")
    plt.legend()

    plt.savefig(output_plot_path, format=FILE_FORMAT, dpi=DPI)

    print(f"Saved {output_plot_path}")

    # plt.show()

    return data


def plot_operators(data: pd.DataFrame, output_plot_path: str) -> None:
    parts = []
    split_size = len(data) // SPLIT
    for i in range(SPLIT):
        if i == SPLIT - 1:  # Include any remaining rows in the last part
            part = data.iloc[i * split_size :]
        else:
            part = data.iloc[i * split_size : (i + 1) * split_size]
        parts.append(part)

    operator_counts = []
    for idx, part in enumerate(parts):
        count = part[CURR_MUTATOR].value_counts()
        operator_counts.append(count)

    fig, axes = plt.subplots(3, 2, figsize=(15, 10))
    axes = axes.flatten()

    for i, count in enumerate(operator_counts):
        ax = axes[i]
        count.plot(kind="bar", ax=ax)
        ax.set_title(f"Operator Counts in Part {i + 1}")
        ax.set_xlabel("Operator")
        ax.set_ylabel("Count")

    axes[-1].axis("off")

    plt.tight_layout()

    plt.savefig(output_plot_path, format=FILE_FORMAT, dpi=DPI)

    print(f"Saved {output_plot_path}")

    # plt.show()


def main() -> None:
    os.makedirs(PLOT_OUTPUT_PATH, exist_ok=True)

    for root, _, files in os.walk(LOG_FILES_PATH):
        for filename in files:
            if filename.endswith(".csv"):
                file_path = os.path.join(root, filename)

                relative_path = os.path.relpath(root, LOG_FILES_PATH)
                output_dir = os.path.join(PLOT_OUTPUT_PATH, relative_path)

                os.makedirs(output_dir, exist_ok=True)

                output_plot_path_data = os.path.join(
                    output_dir, f"{os.path.splitext(filename)[0]}_data.png"
                )

                output_plot_path_operators = os.path.join(
                    output_dir, f"{os.path.splitext(filename)[0]}_operators.png"
                )

                data = run_plot(file_path, output_plot_path_data)
                plot_operators(data, output_plot_path_operators)

                plt.close("all")


if __name__ == "__main__":
    main()
