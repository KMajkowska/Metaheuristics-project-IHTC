import os

import pandas as pd
import matplotlib.pyplot as plt

LOG_FILES_PATH: str = "../log_files_random/"
PLOT_OUTPUT_PATH: str = "../plot_output/"

CURRENT_COL_NAME: str = "res"
BEST_COL_NAME: str = "resBest"
TEMP_COL_NAME: str = "actualTemp"

DPI: int = 400
FILE_FORMAT: str = "png"


def run_plot(csv_file_path: str, output_plot_path: str) -> None:
    data = pd.read_csv(csv_file_path)

    min_value = min(data[CURRENT_COL_NAME].min(), data[BEST_COL_NAME].min())
    max_value = max(data[CURRENT_COL_NAME].max(), data[BEST_COL_NAME].max())

    plt.figure(figsize=(10, 5))
    plt.plot(data[CURRENT_COL_NAME], label="Current", color="blue")
    plt.plot(data[BEST_COL_NAME], label="Best", color="orange")

    plt.ylim(min_value, max_value)

    plt.xlabel("Iteration")
    plt.ylabel("Value")
    plt.title(f"Data Plot (Filtered: Min = {min_value}, Max = {max_value})")
    plt.legend()

    plt.savefig(output_plot_path, format=FILE_FORMAT, dpi=DPI)

    plt.show()


def main() -> None:
    os.makedirs(PLOT_OUTPUT_PATH, exist_ok=True)

    for filename in os.listdir(LOG_FILES_PATH):
        if filename.endswith(".csv") or filename.endswith("txt"):
            file_path = os.path.join(LOG_FILES_PATH, filename)

            output_plot_path = os.path.join(
                PLOT_OUTPUT_PATH, f"{os.path.splitext(filename)[0]}.png"
            )

            run_plot(file_path, output_plot_path)


if __name__ == "__main__":
    main()
