#include "StateController.h"

StateController::StateController() : 
	_workGuard(boost::asio::make_work_guard(_ioContext)),
	_sessionReceiver(_ioContext)
{
	_ioContextThread = std::thread([this]()
		{
			_ioContext.run();
		});
}

StateController& StateController::instance()
{
	static StateController instance;
	return instance;
}

StateController::~StateController()
{
	_workGuard.reset();
	_ioContext.stop();

	if (_ioContextThread.joinable())
	{
		_ioContextThread.join();
	}

	_searchForSessions = false;

	if (_cleanerThread.joinable())
	{
		_cleanerThread.join();
	}
}

void StateController::setAllGameParametersFromJoined(AllGameParameters allGameParameters)
{
	_allGameParameters = allGameParameters;
}

AllGameParameters& StateController::allGameParameters()
{
	return _allGameParameters;
}

std::unordered_map<ScreensNumber, QWidget*>& StateController::screens()
{
	return _screens;
}

void StateController::addScreen(const ScreensNumber screenNumber, QWidget* widget)
{
	if (!_screens.contains(screenNumber))
	{
		_screens[screenNumber] = widget;
	}
}

void StateController::setNavigate(std::function<void(ScreensNumber)> navigateCallback)
{
	_navigateCallback = navigateCallback;
}

void StateController::navigate(ScreensNumber screen)
{
	if (_navigateCallback)
	{
		_navigateCallback(screen);
	}
}

void StateController::setStartGame(std::function<void()> startGameCallback)
{
	_startGameCallback = startGameCallback;
}

void StateController::startGame()
{
	if (_startGameCallback)
	{
		_startGameCallback();
	}
}

std::unordered_map<std::string, CGameInfo>& StateController::foundSessions()
{
	return _foundSessions;
}

void StateController::runComputer(
	std::function<void(std::shared_ptr<ICGame>)> onStart,
	std::function<void()> onFinish, 
	AllGameParameters parameters
) const
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);

	if (!problemDataOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));

	auto game{ std::make_shared<CGameComputer>(std::make_shared<CPlayer>(_allGameParameters.name()), std::make_shared<CPlayer>("stupid computer!"), getWinnerJudge(_allGameParameters), std::move(problemData), Params(parameters)) };
	
	std::thread([game, onFinish, onStart]()
		{
			if (onStart)
			{
				onStart(game);
			}

			game->startGame();

			if (onFinish)
			{
				onFinish();
			}
		}).detach();

}

void StateController::updateSessionList(std::function<void(std::unordered_map<std::string, CGameInfo>&)> consume)
{
	_searchForSessions = true;

	_cleanerThread = std::thread(&StateController::cleaner, this);

	_sessionReceiver.addObserver([this, consume](CGameInfo gameInfo)
		{
			_foundSessions[gameInfo.uuid()] = gameInfo;

			consume(_foundSessions);

			_searchForSessions = false;
		});

	_sessionReceiver.checkForSessions();
}

void StateController::stopUpdatingSessionList()
{
	_searchForSessions = false;

	_sessionReceiver.stopChecking();

	_sessionReceiver.removeObservers();
}

void StateController::createSession(std::function<void(std::shared_ptr<ICGame>)> onStart, std::function<void()> onFinish, AllGameParameters parameters)
{
	std::string problemFile{ getProblemFilePath(parameters.inputParametersLevel()) };

	auto problemDataOpt = jsonToObject<ProblemData>(problemFile);

	if (!problemDataOpt)
	{
		return;
	}

	CGameInfo gameInfo(parameters);

	auto problemData(std::move(problemDataOpt.value()));

	auto poster{ std::make_shared<CSessionPosterPeerToPeer>(_ioContext, gameInfo) };

	auto peer{ std::make_shared<PeerToPeer>(_ioContext, IP, gameInfo.port(), true) };

	auto networkGame{ std::make_shared<CGameNetwork>(peer, std::make_shared<CPlayer>(_allGameParameters.name()), std::make_shared<CPlayer>("enemy"), getWinnerJudge(gameInfo), std::move(problemData), Params(gameInfo))};
	
	peer->setOnEndTransmission([onFinish, peer]()
		{
			peer->tellEndOfTransmission();

			if (onFinish)
			{
				onFinish();
			}
		});

	peer->setOnConnect([poster, networkGame, peer, onStart, onFinish]()
		{
			if (onStart)
			{
				onStart(networkGame);
			}

			poster->stopBroadcast();

			std::thread([networkGame, onFinish, peer]()
			{
				networkGame->startGame();

				if (onFinish)
				{
					onFinish();
				}

				peer->disconnect();
			}).detach();
		});
	
	peer->start();

	poster->postSession();
}

void StateController::joinSession(std::function<void(std::shared_ptr<ICGame>)> onStart, std::function<void()> onFinish, AllGameParameters parameters, CGameInfo chosenGame)
{
	std::string problemFile{ getProblemFilePath(parameters.inputParametersLevel())};

	auto problemDataOpt = jsonToObject<ProblemData>(problemFile);

	if (!problemDataOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));


	auto peer{ std::make_shared<PeerToPeer>(_ioContext, IP, chosenGame.port(), false)};

	auto networkGame{ std::make_shared<CGameNetwork>(peer, std::make_shared<CPlayer>(parameters.name()), std::make_shared<CPlayer>(chosenGame.name()), getWinnerJudge(chosenGame), problemData, Params(parameters)) };


	peer->setOnConnect([networkGame, onStart, onFinish, peer]()
		{
			std::thread([networkGame, onStart, onFinish, peer]()
				{
					if (onStart)
					{
						onStart(networkGame);
					}

					networkGame->startGame();


					if (onFinish)
					{
						onFinish();
					}

					peer->disconnect();
				}).detach();
		});

	peer->start();
}

void StateController::cleaner()
{
	while (_searchForSessions)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::lock_guard<std::mutex> lock(_mtx);

		auto now = std::chrono::steady_clock::now();

		for (auto it = _foundSessions.begin(); it != _foundSessions.end();)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second.lastUpdated()) > TIMEOUT)
			{
				it = _foundSessions.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}
