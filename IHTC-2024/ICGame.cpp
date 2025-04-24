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
	auto result { Winner::NOT_FINISHED };

	while (_judge->checkWinner(*_localPlayer, *_opponentPlayer) == Winner::NOT_FINISHED)
	{
		auto solutionHandler = startRound();

		if (solutionHandler.bestLocal().fitness() < solutionHandler.bestOpponent().fitness())
		{
			*_localPlayer += 1;
		}
		else if (solutionHandler.bestLocal().fitness() > solutionHandler.bestOpponent().fitness())
		{
			*_opponentPlayer += 1;
		}

		if (_consumeScore)
		{
			_consumeScore(result, _localPlayer, _opponentPlayer);
		}
	}

	result = _judge->checkWinner(*_localPlayer, *_opponentPlayer);

	return result;
}

void ICGame::setOnLocal(std::function<void(SolutionData)> onLocal)
{
	_onLocal = onLocal;
}

void ICGame::setOnOpponent(std::function<void(SolutionData)> onOpponent)
{
	_onOpponent = onOpponent;
}

void ICGame::setConsumeScore(std::function<void(Winner, std::shared_ptr<CPlayer>, std::shared_ptr<CPlayer>)> consumeScore)
{
	_consumeScore = consumeScore;
}
