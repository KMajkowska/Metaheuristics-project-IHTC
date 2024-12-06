from dataclasses import dataclass


@dataclass
class Result:
    name: str
    broken_hard_best: int
    broken_soft_best: int
    eval_result_best: float
    broken_hard_worst: int
    broken_soft_worst: int
    eval_result_worst: float
