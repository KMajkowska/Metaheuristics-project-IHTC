#include "StateController.h"

StateController::StateController() : _wordGuard(boost::asio::make_work_guard(_ioContext))
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
	_ioContext.stop();

	if (_ioContextThread.joinable())
	{
		_ioContextThread.join();
	}

	searchForSessions = false;

	if (cleanerThread.joinable())
	{
		cleanerThread.join();
	}
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

void StateController::setSessionConsumer(std::function<void(std::unordered_map<std::string, CGameInfo>&)> sessionConsumer)
{
	_sessionConsumer = sessionConsumer;
}

void StateController::consume(std::unordered_map<std::string, CGameInfo>& sessions)
{
	if (_sessionConsumer)
	{
		_sessionConsumer(sessions);
	}
}

// run in another thread!
// TODO: Parameters choosing
void StateController::runComputer(std::function<void()> onFinish) const
{
	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	CGameComputer game(std::make_shared<CPlayer>(), std::make_shared<CPlayer>(), getWinnerJudge(_allGameParameters), problemData, params);

	game.startGame();

	if (onFinish)
	{
		onFinish();
	}
}

void StateController::updateSessionList()
{
	CSessionReceiverPeerToPeer* sessionReveiver = new CSessionReceiverPeerToPeer(_ioContext);

	searchForSessions = true;

	cleanerThread = std::thread(&StateController::cleaner, this);

	sessionReveiver->addObserver([this, &sessionReveiver](CGameInfo gameInfo)
		{
			foundSessions[gameInfo.uuid()] = gameInfo;

			consume(foundSessions);
		});

	sessionReveiver->checkForSessions();
}

void StateController::createSession(AllGameParameters parameters)
{
	std::string problemFile;

	switch (parameters.inputParametersLevel())
	{
	case(GameLevel::EASY) :
		problemFile = EASY_PROBLEM_FILE;
		break;
	case(GameLevel::MEDIUM):
		problemFile = MEDIUM_PROBLEM_FILE;
		break;
	case(GameLevel::HARD):
		problemFile = HARD_PROBLEM_FILE;
		break;
	default:
		problemFile = DEFAULT_PROBLEM_FILE;
		break;
	}
	auto problemDataOpt = jsonToObject<ProblemData>(problemFile);

	if (!problemDataOpt)
	{
		return;
	}

	CGameInfo gameInfo(parameters);

	auto problemData(std::move(problemDataOpt.value()));

	auto params{ new Params(gameInfo) };

	auto poster{ new CSessionPosterPeerToPeer(_ioContext, gameInfo) };

	auto peer{ std::make_shared<PeerToPeer>(_ioContext, IP, gameInfo.postPort(), gameInfo.receivePort(), true) };

	peer->start();

	auto networkGame{ new CGameNetwork(peer, std::make_shared<CPlayer>(), std::make_shared<CPlayer>(), std::make_shared<BestOfN>(gameInfo.roundNumber()), problemData, *params) };

	peer->addObserver([&poster, &networkGame, &peer](std::string str)
		{
			poster->stopBroadcast();
			networkGame->startGame();
		});

	poster->postSession();
}

void StateController::updateChart()
{

}

void StateController::cleaner()
{
	while (searchForSessions)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::lock_guard<std::mutex> lock(_mtx);

		auto now = (std::chrono::steady_clock::now());

		for (auto it = foundSessions.begin(); it != foundSessions.end();)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second.lastUpdated()) > timeout)
			{
				it = foundSessions.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}
