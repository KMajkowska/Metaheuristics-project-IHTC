#pragma once

#include <unordered_map>
#include <string>


/**
 * @brief Enum class to choose neighbour generator type  
*/
enum class NeighbourGeneratorType
{
	PRIZE_BEST,
	QUEUE,
	TOP,
	TOURNAMENT,
	UNKNOWN
};


const std::unordered_map<NeighbourGeneratorType, std::string> NGT_ENUM_TO_STRING
{
	{NeighbourGeneratorType::PRIZE_BEST, "prizeBest"},
	{NeighbourGeneratorType::QUEUE, "queue"},
	{NeighbourGeneratorType::TOP, "top"},
	{NeighbourGeneratorType::TOURNAMENT, "tournament"},
};