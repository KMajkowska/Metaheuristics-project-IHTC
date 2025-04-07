#pragma once

#include "qstring.h"

enum class GameWinningMode
{
    UNKNOWN,
	BEST_OF_N,
	N_OF_BEST,
};

inline const QString toString(GameWinningMode mode) {
    switch (mode) {
    case GameWinningMode::UNKNOWN:
        return "<empty>";
    case GameWinningMode::BEST_OF_N:
        return "Best of N";
    case GameWinningMode::N_OF_BEST:
        return "N of best";
    default:
        return "Undefined";
    }
}

inline const GameWinningMode toEnumValue(QString mode) {
    if (mode == "<empty>")
        return GameWinningMode::UNKNOWN;
    if (mode == "Best of N")
        return GameWinningMode::BEST_OF_N;
    if (mode == "N of best")
        return GameWinningMode::N_OF_BEST;
    return
        GameWinningMode();
}