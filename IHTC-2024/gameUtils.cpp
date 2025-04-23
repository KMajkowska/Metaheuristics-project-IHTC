#include "gameUtils.h"

std::shared_ptr<IWinnerJudge> getWinnerJudge(const AllGameParameters& params)
{
	switch (params.judgeType())
	{
	case WinnerJudgeType::BEST_OF_N:
		return std::make_shared<BestOfN>(params.roundNumber());
	case WinnerJudgeType::UP_TO_N:
		return std::make_shared<UpToN>(params.roundNumber());
	default:
		throw std::invalid_argument("Incorrect stop criterium");
	}
}

std::string getProblemFilePath(const GameLevel& gameLevel)
{
	switch (gameLevel)
	{
	case GameLevel::EASY:
		return EASY_PROBLEM_FILE;
	case GameLevel::MEDIUM:
		return MEDIUM_PROBLEM_FILE;
	case GameLevel::HARD:
		return HARD_PROBLEM_FILE;
	default:
		return DEFAULT_PROBLEM_FILE;
	}
}
