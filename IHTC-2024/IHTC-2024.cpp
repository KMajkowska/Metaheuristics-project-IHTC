#include <iostream>

#include "params.h"
#include "ProblemData.h"
#include "CGameComputer.h"
#include "CPlayer.h"
#include "BestOfN.h"
#include "PeerToPeer.h"
#include "CGameNetwork.h"
#include "CSessionReceiverPeerToPeer.h"
#include "CSessionPosterPeerToPeer.h"
#include "MainWindow.h"

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

static void joinGame(boost::asio::io_context& context)
{
	auto search = new CSessionReceiverPeerToPeer(context);

	search->addObserver([&search, &context](CGameInfo gameInfo)
		{
			search->stopChecking();

			auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
			auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

			if (!problemDataOpt || !paramsOpt)
			{
				return;
			}

			auto problemData(std::move(problemDataOpt.value()));
			auto params(std::move(paramsOpt.value()));

			auto peer{ std::make_shared<PeerToPeer>(context, IP, gameInfo.receivePort(), gameInfo.postPort(), false) };

			peer->start();

			CGameNetwork networkGame(peer, std::make_shared<CPlayer>(), std::make_shared<CPlayer>(), std::make_shared<BestOfN>(gameInfo.roundNumber()), problemData, params);

			networkGame.startGame();
		});

	search->checkForSessions();
}

static void hostGame(boost::asio::io_context& context)
{
	CGameInfo gameInfo;

	gameInfo.setJudgeType(WinnerJudgeType::BEST_OF_N);
	gameInfo.setName("Host");
	gameInfo.setPostPort(8082);
	gameInfo.setReceivePort(8083);
	gameInfo.setRoundNumber(5);

	CSessionPosterPeerToPeer poster(context, gameInfo);

	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	auto peer{ std::make_shared<PeerToPeer>(context, IP, gameInfo.postPort(), gameInfo.receivePort(), true) };

	peer->start();

	auto networkGame{ new CGameNetwork(peer, std::make_shared<CPlayer>(), std::make_shared<CPlayer>(), std::make_shared<BestOfN>(gameInfo.roundNumber()), problemData, params) };

	peer->addObserver([&poster, &networkGame, &peer](std::string str)
		{
			poster.stopBroadcast();
			networkGame->startGame();
		});

	poster.postSession();


	std::cout << "FINITO GAME" << std::endl;
}

static void runJustGame(short postPort, short receivePort)
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	auto ioContext{ std::make_shared<boost::asio::io_context>() };
	auto workGuard{ boost::asio::make_work_guard(ioContext) };

	auto peer{ std::make_shared<PeerToPeer>(*ioContext, IP, postPort, receivePort, false) };

	peer->setOnConnect([&peer, &problemData, &params]()
		{
			std::cout << "Peer connected. Starting game..." << std::endl;

			auto networkGame = std::make_shared<CGameNetwork>(
				peer,
				std::make_shared<CPlayer>(),
				std::make_shared<CPlayer>(),
				std::make_shared<BestOfN>(5),
				std::move(problemData),
				std::move(params)
			);

			networkGame->startGame();
		});

	peer->start();

	std::cout << "Joining the game, waiting for connection..." << std::endl;

	std::thread ioThread([ioContext]()
		{
			ioContext->run();
		});

	ioThread.join();

	std::cout << "FINITO" << std::endl;
}

static void runJustHost(int postPort, int receivePort)
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	auto ioContext { std::make_shared<boost::asio::io_context>() };
	auto workGuard{ boost::asio::make_work_guard(ioContext) };

	auto peer{ std::make_shared<PeerToPeer>(*ioContext, IP, postPort, receivePort, true) };

	peer->setOnConnect([&peer, &problemData, &params]()
		{
			std::cout << "Peer connected. Starting game..." << std::endl;

			// Now, start the game after the peer connection is established
			auto networkGame = std::make_shared<CGameNetwork>(
				peer,
				std::make_shared<CPlayer>(),
				std::make_shared<CPlayer>(),
				std::make_shared<BestOfN>(5),
				std::move(problemData),
				std::move(params)
			);
			networkGame->startGame();
		});

	peer->start();

	std::cout << "Hosting the game, waiting for connection..." << std::endl;

	std::thread ioThread([ioContext]()
		{
			ioContext->run();
		});

	ioThread.join();

	std::cout << "FINITO" << std::endl;
}

static void runNetworkTest(int sendPort, int receivePort, bool isHost)
{
	if (isHost)
	{
		// hostGame();
		runJustHost(sendPort, receivePort);
	}
	else
	{
		// joinGame();
		runJustGame(sendPort, receivePort);
	}
}

static void runNetworkTestjustPeer(int argc, char* argv[])
{
	boost::asio::io_context ioContext;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard = boost::asio::make_work_guard(ioContext);

	std::string ip = "127.0.0.1";
	int sendPort = 8082;
	int receivePort = 8083;
	bool isHost = (argc > 1 && std::string(argv[1]) == "host");

	PeerToPeer peer(ioContext, ip, isHost ? sendPort : receivePort, isHost ? receivePort : sendPort, isHost);

	peer.setOnConnect([&peer, &isHost]() 
		{
			std::cout << "CONNECTED" << std::endl; 

			peer.sendMessage(isHost ? "Hello World! Host speaking" : "Hello world! Client speaking");
		});
	peer.setOnClose([]() {std::cout << "STOPPED" << std::endl; });
	peer.addObserver([](const std::string str) { std::cout << str << std::endl; });
	peer.start();

	std::thread ioThread([&ioContext]()
		{
			std::cout << "Starting Boost.Asio IO context..." << std::endl;
			ioContext.run();
		});

	ioThread.join();
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;

	mainWindow.resize(1100, 800);
	mainWindow.show();

	return app.exec();
	try
	{
		auto sendPort{ argc > 1 ? atoi(argv[1]) : 8081 };
		auto receivePort{ argc > 2 ? atoi(argv[2]) : 8082 };
		auto isHostNum{ argc > 3 ? atoi(argv[3]) : 1 };

		runNetworkTest(sendPort, receivePort, isHostNum != 0);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return 1;
	}

	return 0;
}
