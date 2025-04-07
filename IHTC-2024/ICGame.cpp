#include "ICGame.h"

ICGame::ICGame(
	std::shared_ptr<CPlayer> localPlayer,
	std::shared_ptr<CPlayer> opponentPlayer,
	std::shared_ptr<IWinnerJudge> judge,
	const ProblemData problemData,
	const Params params
) :
	_localPlayer(localPlayer),
	_opponentPlayer(opponentPlayer),
	_judge(judge),
	_problemData(problemData),
	_localParams(params)
{}

Winner ICGame::startGame()
{
	// Logger::log("Start game");

	auto result { Winner::NOT_FINISHED };

	while (_judge->checkWinner(*_localPlayer, *_opponentPlayer) == Winner::NOT_FINISHED)
	{
		std::cout << std::format("Current result is: {0}, score: {1} to {2}", enumToString(result), std::to_string(_localPlayer->score()), std::to_string(_opponentPlayer->score())) << std::endl;

		auto result = startRound();

		std::cout << "results " << result.bestLocal().fitness() << " to " << result.bestOpponent().fitness() << std::endl;

		if (result.bestLocal().fitness() < result.bestOpponent().fitness())
		{
			std::cout << "Local won this round" << std::endl;
			*_localPlayer += 1;
		}
		else if (result.bestLocal().fitness() > result.bestOpponent().fitness())
		{
			std::cout << "Opponent won this round" << std::endl;
			*_opponentPlayer += 1;
		}
	}

	return result;
}
