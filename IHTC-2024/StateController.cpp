#include "StateController.h"

StateController& StateController::instance()
{
	static StateController instance;
	return instance;
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

void StateController::setSessionConsumer(std::function<void(std::unordered_map<std::string, CGameInfo>)> sessionConsumer)
{
	_sessionConsumer = sessionConsumer;
}

void StateController::consume(std::unordered_map<std::string, CGameInfo> sessions)
{
	if (_sessionConsumer)
	{
		_sessionConsumer(sessions);
	}
}

// run in another thread!
void StateController::runComputer(std::function<void()> onFinish)
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
	boost::asio::io_context ioContext;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> workGuard = boost::asio::make_work_guard(ioContext);
	CSessionReceiverPeerToPeer* sessionReveiver = new CSessionReceiverPeerToPeer(ioContext);

	cleanerThread = std::thread(&StateController::cleaner, this);

	sessionReveiver->addObserver([this, &sessionReveiver, &ioContext](CGameInfo gameInfo)
		{
			foundSessions[gameInfo.uuid()] = gameInfo;

			consume(foundSessions);
		});

	sessionReveiver->checkForSessions();

	if (cleanerThread.joinable())
	{
		cleanerThread.join();
	}
}

void StateController::cleaner() {
	searchForSessions = true;

	while (searchForSessions)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::lock_guard<std::mutex> lock(_mtx);

		auto now = (std::chrono::steady_clock::now());

		for (auto it = foundSessions.begin(); it != foundSessions.end();)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second.lastUpdated()) > timeout) {
				std::cout << "Removing session: " << it->first << std::endl;
				it = foundSessions.erase(it);
			}
			else {
				++it;
			}
		}
	}
}
