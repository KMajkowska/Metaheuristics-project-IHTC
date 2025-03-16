#pragma once

#include <unordered_map>
#include <string>

#include "strings.h"


enum class SolverType
{
	SA,
	RAND,
	GREEDY,
	UNKNOWN
};

const std::string SA = "sa";
const std::string RAND = "rand";
const std::string GREEDY = "greedy";

const std::unordered_map<std::string, SolverType> ST_STRING_TO_ENUM
{
	{SA, SolverType::SA},
	{RAND, SolverType::RAND},
	{GREEDY, SolverType::GREEDY},
};

const std::unordered_map<SolverType, std::string> ST_ENUM_TO_STRING
{
	{SolverType::SA, SA},
	{SolverType::RAND, RAND},
	{SolverType::GREEDY, GREEDY},
};
