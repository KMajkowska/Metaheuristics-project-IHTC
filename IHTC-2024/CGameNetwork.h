#pragma once

#include "ICGame.h"
#include "CSolutionDataHandlerNetwork.h"

class CGameNetwork : public ICGame
{
	CGameNetwork(
		std::shared_ptr<INetworkExchanger> exchanger,
		std::shared_ptr<CPlayer> localPlayer,
		std::shared_ptr<CPlayer> opponentPlayer,
		std::shared_ptr<IWinnerJudge> judge,
		const ProblemData& problemData,
		const Params& params
	);

	CSolutionHandler startRound() override;

private:
	std::shared_ptr<INetworkExchanger> _exchanger;

};