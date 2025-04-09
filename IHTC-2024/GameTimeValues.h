#pragma once

#include <unordered_map>
#include <string>

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

const std::unordered_map<GameTimeValues, std::string> GTV_ENUM_TO_STRING
{
    {GameTimeValues::UNKNOWN, "<empty>"},
    {GameTimeValues::_30, "30 seconds"},
    {GameTimeValues::_60, "60 seconds"},
    {GameTimeValues::_90, "90 seconds"},
    {GameTimeValues::_120, "120 seconds"},
    {GameTimeValues::_150, "150 seconds"},
    {GameTimeValues::_180, "180 seconds"}
};

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