#include "SolverType.h"

SolverType solverTypeFromJson(const std::string& colorStr)
{
    std::string lower = tolowercase(colorStr);

    auto it = STRING_TO_SOLVER_TYPE.find(lower);

    if (it != STRING_TO_SOLVER_TYPE.end())
    {
        return it->second;
    }

    return SolverType::UNKNOWN;
}

std::string solverTypeToJson(SolverType type)
{
    auto it = SOLVER_TYPE_TO_STRING.find(type);

    if (it != SOLVER_TYPE_TO_STRING.end())
    {
        return it->second;
    }

    return SOLVER_TYPE_TO_STRING.at(SolverType::UNKNOWN);
}
