#pragma once

#include <unordered_map>
#include <string>

/**
 * @brief enum for stop criterium type, which is determined by user, but its controls game to stop
*/

enum class StopCriteriumType
{
	TEMPERATURE,
	ITERATION,
	TIME,
	UNKNOWN
};

const std::unordered_map<StopCriteriumType, std::string> SCT_ENUM_TO_STRING
{
	{StopCriteriumType::TEMPERATURE, "temperature"},
	{StopCriteriumType::ITERATION, "iteration"},
	{StopCriteriumType::TIME, "time"},
};