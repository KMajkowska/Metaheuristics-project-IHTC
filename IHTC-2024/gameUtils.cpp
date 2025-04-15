#include "gameUtils.h"

std::shared_ptr<IWinnerJudge> getWinnerJudge(const AllGameParameters& params)
{
	switch (params.judgeType())
	{
	case WinnerJudgeType::BEST_OF_N:
		return std::make_shared<BestOfN>(params.roundNumber());
	default:
		throw std::invalid_argument("Incorrect stop criterium");
	}
}
