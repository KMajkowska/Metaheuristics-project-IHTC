#pragma once

#include <qwidget.h>

#include "ScreensNumber.h"
#include "CGameComputer.h"
#include "gameUtils.h"
#include "constants.h"
#include "params.h"
#include "JSONOperations.h"
#include "CSessionReceiverPeerToPeer.h"
#include "CSessionPosterPeerToPeer.h"
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <consts.h>
#include "PeerToPeer.h"
#include "CGameNetwork.h"

/**
 * @brief Class to control game state
*/
class StateController
{
public:
	static StateController& instance();
	~StateController();

	void setAllGameParametersFromJoined(AllGameParameters allGameParameters);
	AllGameParameters& allGameParameters();

	std::unordered_map<ScreensNumber, QWidget*>& screens();
	void addScreen(const ScreensNumber, QWidget* widget);

	void setNavigate(std::function<void(ScreensNumber)> navigateCallback);
	void navigate(ScreensNumber screen);

	void setStartGame(std::function<void()> startGameCallback);
	void startGame();

	void updateSessionList(std::function<void(std::unordered_map<std::string, CGameInfo>&)> consume);
	void stopUpdatingSessionList();
	std::unordered_map<std::string, CGameInfo>& foundSessions();

	void runComputer(std::function<void(std::shared_ptr<ICGame>)> onStart, std::function<void()> onFinish, AllGameParameters parameter) const;
	void createSession(std::function<void(std::shared_ptr<ICGame>)> onStart, std::function<void()> onFinish, AllGameParameters parameters);
	void joinSession(std::function<void(std::shared_ptr<ICGame>)> onStart, std::function<void()> onFinish, AllGameParameters parameters, CGameInfo chosenGame);

private:
	std::function<void(ScreensNumber)> _navigateCallback;
	std::function<void()> _startGameCallback;

	std::unordered_map<ScreensNumber, QWidget*> _screens;
	AllGameParameters _allGameParameters;

	boost::asio::io_context _ioContext;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard;
	std::thread _ioContextThread;

	std::unordered_map<std::string, CGameInfo> _foundSessions;

	CSessionReceiverPeerToPeer _sessionReceiver;
	bool _searchForSessions{false};
	std::thread _cleanerThread;
	std::mutex _mtx;

	const std::chrono::milliseconds TIMEOUT{ (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(TIMEOUT_SECONDS))) };

	void cleaner();

	StateController();
};