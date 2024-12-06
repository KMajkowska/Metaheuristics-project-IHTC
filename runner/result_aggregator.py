import os
from typing import List, Optional

import pandas as pd

from Result import Result
from consts import (
    RES_CURRENT_COL_NAME,
    COUNT_TOTAL_HARD,
    COUNT_TOTAL_SOFT,
    LOG_FILES_PATH,
    AGGREGATED_RESULT_PATH,
)


def find_result(file_path: str, folder_name: str) -> Optional[Result]:
    file_name = os.path.basename(file_path)

    try:
        if file_path.endswith(".csv"):
            df = pd.read_csv(file_path)
        elif file_path.endswith(".xlsx"):
            df = pd.read_excel(file_path)
        else:
            return None

        best_row = df.loc[df[RES_CURRENT_COL_NAME].idxmin()]
        worst_row = df.loc[df[RES_CURRENT_COL_NAME].idxmax()]

        return Result(
            name=f"{folder_name} {file_name}",
            broken_hard_best=best_row[COUNT_TOTAL_HARD],
            broken_soft_best=best_row[COUNT_TOTAL_SOFT],
            eval_result_best=best_row[RES_CURRENT_COL_NAME],
            broken_hard_worst=worst_row[COUNT_TOTAL_HARD],
            broken_soft_worst=worst_row[COUNT_TOTAL_SOFT],
            eval_result_worst=worst_row[RES_CURRENT_COL_NAME],
        )
    except (Exception,):
        return None


def aggregate_folder_data_to_excel(folder_path: str) -> List[Result]:
    aggregated_data: List[Result] = []

    for root, dirs, files in os.walk(folder_path):
        folder_name = os.path.basename(root)

        for file in files:
            file_path = os.path.join(root, file)

            res = find_result(file_path, folder_name)

            if res:
                aggregated_data.append(res)

    return aggregated_data


def main() -> None:
    output_path = AGGREGATED_RESULT_PATH

    result = aggregate_folder_data_to_excel(LOG_FILES_PATH)

    result_df = pd.DataFrame(result)

    result_df.to_excel(output_path, index=False)

    print(f"Aggregated data saved to {output_path}")


if __name__ == "__main__":
    main()
