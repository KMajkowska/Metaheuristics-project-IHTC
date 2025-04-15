#pragma once

#include <qwidget.h>

#include "ScreensNumber.h"
#include "AllGameParameters.h"
#include "CGameComputer.h"
#include "gameUtils.h"
#include "constants.h"
#include "params.h"
#include "JSONOperations.h"

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

	void runComputer(std::function<void()> onFinish);

private:
	std::unordered_map<ScreensNumber, QWidget*> _screens;
	AllGameParameters _allGameParameters;
	std::function<void(ScreensNumber)> _navigateCallback;

	StateController() = default;
};