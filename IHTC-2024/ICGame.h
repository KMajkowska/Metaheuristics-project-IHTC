#pragma once

#include <memory>

#include "IWinnerJudge.h"
#include "params.h"
#include "ProblemData.h"
#include "CSolutionHandler.h"

/**
 * @brief Class used as an interface to provide polymorphism of game with player and computer
*/
class ICGame
{
public:	
	ICGame(
		std::shared_ptr<CPlayer> localPlayer, 
		std::shared_ptr<CPlayer> opponentPlayer, 
		std::shared_ptr<IWinnerJudge> judge, 
		const ProblemData problemData, 
		const Params params
	);

	Winner startGame();

	void setOnLocal(std::function<void(SolutionData)> onLocal);
	void setOnOpponent(std::function<void(SolutionData)> onOpponent);

protected:
	std::shared_ptr<CPlayer> _localPlayer;
	std::shared_ptr<CPlayer> _opponentPlayer;

	std::shared_ptr<IWinnerJudge> _judge;

	const Params _localParams;
	const ProblemData _problemData;

	std::function<void(SolutionData)> _onLocal;
	std::function<void(SolutionData)> _onOpponent;

	virtual CSolutionHandler startRound() = 0;
};