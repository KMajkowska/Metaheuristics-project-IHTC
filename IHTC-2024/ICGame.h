#pragma once

#include <memory>

#include "IWinnerJudge.h"
#include "params.h"
#include "ProblemData.h"
#include "CSolutionHandler.h"

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

protected:
	std::shared_ptr<CPlayer> _localPlayer;
	std::shared_ptr<CPlayer> _opponentPlayer;

	std::shared_ptr<IWinnerJudge> _judge;

	const Params _localParams;
	const ProblemData _problemData;

	virtual CSolutionHandler startRound() = 0;
};