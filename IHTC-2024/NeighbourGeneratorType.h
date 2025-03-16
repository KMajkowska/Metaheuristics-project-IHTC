#pragma once

#include <unordered_map>
#include <string>

#include "strings.h"

enum class NeighbourGeneratorType
{
	PRIZE_BEST,
	QUEUE,
	TOP,
	TOURNAMENT,
	UNKNOWN
};

const std::string PRIZE_BEST = "prizeBest";
const std::string QUEUE = "queue";
const std::string TOP = "top";
const std::string TOURNAMENT = "tournament";

const std::unordered_map<std::string, NeighbourGeneratorType> NGT_STRING_TO_ENUM
{
	{PRIZE_BEST, NeighbourGeneratorType::PRIZE_BEST},
	{QUEUE, NeighbourGeneratorType::QUEUE},
	{TOP, NeighbourGeneratorType::TOP},
	{TOURNAMENT, NeighbourGeneratorType::TOURNAMENT}
};

const std::unordered_map<NeighbourGeneratorType, std::string> NGT_ENUM_TO_STRING
{
	{NeighbourGeneratorType::PRIZE_BEST, PRIZE_BEST},
	{NeighbourGeneratorType::QUEUE, QUEUE},
	{NeighbourGeneratorType::TOP, TOP},
	{NeighbourGeneratorType::TOURNAMENT, TOURNAMENT},
};