#pragma once

#include <unordered_map>
#include <string>

/**
 * @brief Enum for choosing solver
*/
enum class SolverType
{
	SA,
	RAND,
	GREEDY,
	UNKNOWN
};

const std::unordered_map<SolverType, std::string> ST_ENUM_TO_STRING
{
	{SolverType::SA, "sa"},
	{SolverType::RAND, "rand"},
	{SolverType::GREEDY, "greedy"},
};
