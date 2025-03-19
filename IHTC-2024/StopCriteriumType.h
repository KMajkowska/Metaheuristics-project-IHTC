#pragma once

#include <unordered_map>
#include <string>

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