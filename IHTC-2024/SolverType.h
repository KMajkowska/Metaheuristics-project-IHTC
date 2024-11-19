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

const std::unordered_map<std::string, SolverType> STRING_TO_SOLVER_TYPE
{
    {"sa", SolverType::SA},
    {"rand", SolverType::RAND},
    {"greedy", SolverType::GREEDY}
};

const std::unordered_map<SolverType,std::string> SOLVER_TYPE_TO_STRING
{
    {SolverType::SA, "sa"},
    {SolverType::RAND,"rand"},
    {SolverType::GREEDY, "greedy"},
    {SolverType::UNKNOWN, "unknown"}
};

SolverType solverTypeFromJson(const std::string& colorStr);

std::string solverTypeToJson(SolverType type);