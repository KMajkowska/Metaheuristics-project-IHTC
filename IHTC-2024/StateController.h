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

class StateController
{
public:
	static StateController& instance();
	~StateController();

	AllGameParameters& allGameParameters();

	std::unordered_map<ScreensNumber, QWidget*>& screens();
	void addScreen(const ScreensNumber, QWidget* widget);

	void setNavigate(std::function<void(ScreensNumber)> navigateCallback);
	void navigate(ScreensNumber screen);

	void setSessionConsumer(std::function<void(std::unordered_map<std::string, CGameInfo>&)> sessionCOnsumer);
	void consume(std::unordered_map<std::string, CGameInfo>& sessions);

	void runComputer(std::function<void()> onFinish) const;

	void updateSessionList();

	void createSession(AllGameParameters parameters);

private:
	std::function<void(ScreensNumber)> _navigateCallback;
	std::function<void(std::unordered_map<std::string, CGameInfo>&)> _sessionConsumer;

	std::unordered_map<ScreensNumber, QWidget*> _screens;
	AllGameParameters _allGameParameters;

	boost::asio::io_context _ioContext;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _wordGuard;
	std::thread _ioContextThread;

	std::unordered_map<std::string, CGameInfo> foundSessions;

	void cleaner();
	bool searchForSessions{false};
	std::thread cleanerThread;

	std::mutex _mtx;

	const std::chrono::milliseconds timeout{ (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(TIMEOUT_SECONDS))) };

	StateController();
};