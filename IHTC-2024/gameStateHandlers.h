#pragma once

#include "Winner.h"
#include "endGame.h"
#include "sessions.h"
#include "StateController.h"

void showWinner(Winner winner);

void showPlot(std::shared_ptr<ICGame> game);
