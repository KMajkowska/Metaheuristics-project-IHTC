#pragma once

#include "qstring.h"

enum class GameTimeValues
{
    UNKNOWN,
	_30,
	_60,
	_90,
    _120,
    _150,
    _180
};

inline QString toString(GameTimeValues time) {
    switch (time) {
    case GameTimeValues::UNKNOWN:
        return "<empty>";
    case GameTimeValues::_30:
        return "30 seconds";
    case GameTimeValues::_60:
        return "60 seconds";
    case GameTimeValues::_90:
        return "90 seconds";
    case GameTimeValues::_120:
        return "120 seconds";
    case GameTimeValues::_150:
        return "150 seconds";
    case GameTimeValues::_180:
        return "180 seconds";
    default:
        return "Undefined";
    }
}

inline int toInt(QString time) {
    if (time == "<empty>")
        return 0;
    if (time == "30 seconds")
        return 30;
    if (time == "60 seconds")
        return 60;
    if (time == "90 seconds")
        return 90;
    if (time == "120 seconds")
        return 120;
    if (time == "150 seconds")
        return 150;
    if (time == "180 seconds")
        return 180;
    return -1;

}