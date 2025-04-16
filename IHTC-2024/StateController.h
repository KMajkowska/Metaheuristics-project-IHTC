#pragma once

#include <qwidget.h>

#include "ScreensNumber.h"
#include "AllGameParameters.h"
#include "CGameComputer.h"
#include "gameUtils.h"
#include "constants.h"
#include "params.h"
#include "JSONOperations.h"
#include "CSessionReceiverPeerToPeer.h"
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <consts.h>

class StateController
{
public:
	static StateController& instance();
	~StateController() = default;

	AllGameParameters& allGameParameters();

	std::unordered_map<ScreensNumber, QWidget*>& screens();
	void addScreen(const ScreensNumber, QWidget* widget);

	void setNavigate(std::function<void(ScreensNumber)> navigateCallback);
	void navigate(ScreensNumber screen);

	void setSessionConsumer(std::function<void(std::unordered_map<std::string, CGameInfo>)> sessionCOnsumer);
	void consume(std::unordered_map<std::string, CGameInfo> sessions);

	void runComputer(std::function<void()> onFinish);

	void updateSessionList();

private:
	std::function<void(ScreensNumber)> _navigateCallback;
	std::function<void(std::unordered_map<std::string, CGameInfo>)> _sessionConsumer;

	std::unordered_map<ScreensNumber, QWidget*> _screens;
	AllGameParameters _allGameParameters;

	std::unordered_map<std::string, CGameInfo> foundSessions;

	void cleaner();
	bool searchForSessions;
	std::thread cleanerThread;

	std::mutex _mtx;

	const std::chrono::milliseconds timeout{ (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(TIMEOUT_SECONDS))) };

	StateController() = default;
};