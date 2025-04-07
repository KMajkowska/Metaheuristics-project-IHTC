#pragma once

#include "qstring.h"

enum class GameLevel
{
    UNKNOWN,
    EASY,
    MEDIUM,
    HARD
};

inline QString toString(GameLevel level) {
    switch (level) {
    case GameLevel::UNKNOWN:
        return "<empty>";
    case GameLevel::EASY:
        return "Easy";
    case GameLevel::MEDIUM:
        return "Medium";
    case GameLevel::HARD:
        return "Hard";
    default:
        return "Undefined";
    }
}

inline GameLevel toEnum(QString level) {
    if(level == "<empty>")
        return GameLevel::UNKNOWN;
    if (level == "Easy")
        return GameLevel::EASY;
    if (level == "Medium")
        return GameLevel::MEDIUM;
    if (level == "Hard")
        return GameLevel::HARD;
    return
        GameLevel();
}