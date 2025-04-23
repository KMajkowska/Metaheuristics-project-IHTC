#pragma once

#include <memory>
#include <stdexcept>

#include "BestOfN.h"
#include "IWinnerJudge.h"
#include "AllGameParameters.h"
#include "constants.h"

/**
 * @brief Method that returns winner judge based on params input by the user
 * @param params configured params
 * @return judge based on params
*/
std::shared_ptr<IWinnerJudge> getWinnerJudge(const AllGameParameters& params);

std::string getProblemFilePath(const GameLevel& gameLevel);
