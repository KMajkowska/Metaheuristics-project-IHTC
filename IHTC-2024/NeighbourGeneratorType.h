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

const std::unordered_map<std::string, NeighbourGeneratorType> STRING_TO_NEIGHBOUR_GENERATOR_TYPE
{
    {"prizebest", NeighbourGeneratorType::PRIZE_BEST},
    {"queue", NeighbourGeneratorType::QUEUE},
    {"top", NeighbourGeneratorType::TOP},
    {"tournament", NeighbourGeneratorType::TOURNAMENT}
};

const std::unordered_map<NeighbourGeneratorType, std::string> NEIGHBOUR_GENERATOR_TYPE_TO_STRING
{
    {NeighbourGeneratorType::PRIZE_BEST, "prizeBest"},
    {NeighbourGeneratorType::QUEUE, "queue"},
    {NeighbourGeneratorType::TOP, "top"},
    {NeighbourGeneratorType::TOURNAMENT, "tournament"},
    {NeighbourGeneratorType::UNKNOWN, "unknown"}
};

NeighbourGeneratorType neighbourGeneratorTypeFromJson(const std::string& str);

std::string neighbourGeneratorTypeToJson(NeighbourGeneratorType type);