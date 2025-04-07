#pragma once

#include <future>

#include "ICGame.h"
#include "CSolutionDataHandlerNetwork.h"
#include "CIndividualObservable.h"
#include "FitnessCalculator.h"
#include "IHTCProblem.h"
#include "solverBuilderUtils.h"

class CGameNetwork : public ICGame
{
public:
	CGameNetwork(
		std::shared_ptr<INetworkExchanger> exchanger,
		std::shared_ptr<CPlayer> localPlayer,
		std::shared_ptr<CPlayer> opponentPlayer,
		std::shared_ptr<IWinnerJudge> judge,
		const ProblemData problemData,
		const Params params
	);

protected:
	CSolutionHandler startRound() override;

private:
	std::shared_ptr<INetworkExchanger> _exchanger;

};