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
