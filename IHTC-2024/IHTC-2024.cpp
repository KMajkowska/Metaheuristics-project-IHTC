#include <iostream>

#include "constants.h"
#include "JSONOperations.h"
#include "params.h"
#include "ProblemData.h"
#include "CGameComputer.h"
#include "CPlayer.h"
#include "BestOfN.h"
#include "PeerToPeer.h"
#include "CGameNetwork.h"
#include "CSessionReceiverPeerToPeer.h"
#include "CSessionPosterPeerToPeer.h"

static void runLocalTest()
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	CGameComputer game(std::make_shared<CPlayer>(), std::make_shared<CPlayer>(), std::make_shared<BestOfN>(3), problemData, params);

	game.startGame();
}

static void searchPeers()
{
	CSessionReceiverPeerToPeer search;

	search.addObserver([&search](CGameInfo gameInfo)
		{
			auto jsonOpt{ objectToJson<CGameInfo>(gameInfo) };

			if (jsonOpt)
			{
				std::cout << jsonOpt.value() << std::endl;

				search.stopChecking();
			}
		});

	search.checkForSessions();
}

static void postSessionToPeers()
{
	CGameInfo gameInfo;

	CSessionPosterPeerToPeer poster(gameInfo);

	poster.postSession();
}

static void runNetworkGame(int sendPort, int recievePort, bool isHost)
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto peer{ std::make_shared<PeerToPeer>(IP, sendPort, recievePort, isHost) };
}

static void runNetworkTest(int argc, char* argv[])
{
	auto sendPort{ argc > 1 ? (short)atoi(argv[1]) : 5001 };
	auto recievePort{ argc > 2 ? (short)atoi(argv[2]) : 5000 };

	auto isHost { sendPort == 5000 };

	if (isHost)
	{
		postSessionToPeers();
	}
	else
	{
		searchPeers();
	}
}

int main(int argc, char* argv[])
{
	try
	{
		// runLocal();
		runNetworkTest(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return 1;
	}

	return 0;
}
