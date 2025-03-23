#pragma once

#include <future>

#include "ICGame.h"
#include "CIndividualObservable.h"
#include "FitnessCalculator.h"
#include "IHTCProblem.h"
#include "solverBuilderUtils.h"

class CGameComputer : public ICGame
{
public:
	CGameComputer(
		std::shared_ptr<CPlayer> localPlayer,
		std::shared_ptr<CPlayer> opponentPlayer,
		std::shared_ptr<IWinnerJudge> judge,
		const ProblemData& problemData,
		const Params& params
	);

	CSolutionHandler startRound() override;
};