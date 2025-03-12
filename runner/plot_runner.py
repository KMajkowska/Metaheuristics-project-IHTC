import os

import pandas as pd
import matplotlib.pyplot as plt

from consts import (
    PLOT_OUTPUT_PATH,
    RES_CURRENT_COL_NAME,
    RES_BEST_COL_NAME,
    RES_WORST_NEIGHBOUR,
    RES_BEST_NEIGHBOUR,
    RES_AVG_NEIGHBOUR,
    FILE_FORMAT,
    DPI,
    SPLIT,
    CURR_MUTATOR,
    PLOT_OPERATORS,
    LOG_FILES_PATH,
    TEMP_COL_NAME
)


def run_plot(csv_file_path: str, output_plot_path: str) -> pd.DataFrame:
    all_data = pd.read_csv(csv_file_path)

    # Filter out initial spikes in search
    midpoint = len(all_data) // 3  # Adjust to correctly take the midpoint
    data = all_data.iloc[midpoint:].copy()

    # Handle missing or invalid values
    data = data.replace([float("inf"), -float("inf")], float("nan")).dropna()

    if data.empty:
        print(f"No valid data to plot in file: {csv_file_path}")
        return pd.DataFrame()

    # Recalculate min and max values for fitness plotting
    min_value = min(
        data[RES_CURRENT_COL_NAME].min(),
        data[RES_BEST_COL_NAME].min(),
        data[RES_WORST_NEIGHBOUR].min(),
        data[RES_BEST_NEIGHBOUR].min(),
    )
    max_value = max(
        data[RES_CURRENT_COL_NAME].max(),
        data[RES_BEST_COL_NAME].max(),
        data[RES_WORST_NEIGHBOUR].max(),
        data[RES_BEST_NEIGHBOUR].max(),
    )

    # Create the main plot with a secondary Y-axis
    fig, ax1 = plt.subplots(figsize=(30, 15))

    # Plot fitness-related data on the left Y-axis
    ax1.plot(data[RES_WORST_NEIGHBOUR], label="Worst neighbour", color="yellow")
    ax1.plot(data[RES_AVG_NEIGHBOUR], label="Avg neighbour", color="red")
    ax1.plot(data[RES_BEST_COL_NAME], label="Best", color="green")
    ax1.plot(data[RES_CURRENT_COL_NAME], label="Current", color="blue")

    ax1.set_ylim(min_value, max_value)
    ax1.set_xlabel("Iteration")
    ax1.set_ylabel("Fitness")
    ax1.set_title(f"Simulated Annealing (Min = {min_value}, Max = {max_value})")
    ax1.legend(loc="upper left")

    # Create a second Y-axis for temperature
    if TEMP_COL_NAME in data.columns:
        ax2 = ax1.twinx()
        ax2.plot(data[TEMP_COL_NAME], label="Temperature", color="orange", linestyle="--")
        ax2.set_ylabel("Temperature")
        ax2.legend(loc="upper right")

    # Save the plot
    plt.savefig(output_plot_path, format=FILE_FORMAT, dpi=DPI)

    print(f"Saved {output_plot_path}")

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


def generate_plots(root: str, filename: str, file_dir: str) -> None:
    file_path = os.path.join(root, filename)

    relative_path = os.path.relpath(root, file_dir)
    output_dir = os.path.join(PLOT_OUTPUT_PATH, relative_path)

    os.makedirs(output_dir, exist_ok=True)

    output_plot_path_data = os.path.join(
        output_dir, f"{os.path.splitext(filename)[0]}_data.png"
    )

    output_plot_path_operators = os.path.join(
        output_dir, f"{os.path.splitext(filename)[0]}_operators.png"
    )

    data = run_plot(file_path, output_plot_path_data)

    if PLOT_OPERATORS:
        plot_operators(data, output_plot_path_operators)

    plt.close("all")


def main() -> None:
    file_dir = LOG_FILES_PATH

    os.makedirs(PLOT_OUTPUT_PATH, exist_ok=True)

    for root, _, files in os.walk(file_dir):
        for filename in files:
            if filename.endswith(".csv"):
                generate_plots(root, filename, file_dir)


if __name__ == "__main__":
    main()
