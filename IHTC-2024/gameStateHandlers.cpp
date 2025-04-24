#include "gameStateHandlers.h"

void showWinner(Winner winner)
{
	static_cast<Ui_endGameScreen*>(StateController::instance().screens()[ScreensNumber::END_GAME_SCREEN])->changeGameResultLabel(winner);
	StateController::instance().navigate(ScreensNumber::END_GAME_SCREEN);
}

void showPlot(std::shared_ptr<ICGame> game)
{
	static_cast<Ui_gamePlotScreen*>(StateController::instance().screens()[ScreensNumber::PLOT_SCREEN])->connectPlot(game);
	StateController::instance().navigate(ScreensNumber::PLOT_SCREEN);
}
