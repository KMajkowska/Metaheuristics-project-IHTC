#include "NeighbourGeneratorType.h"

NeighbourGeneratorType neighbourGeneratorTypeFromJson(const std::string& str)
{
    std::string lower = tolowercase(str);

    auto it = STRING_TO_NEIGHBOUR_GENERATOR_TYPE.find(lower);

    if (it != STRING_TO_NEIGHBOUR_GENERATOR_TYPE.end())
    {
        return it->second;
    }

    return NeighbourGeneratorType::UNKNOWN;
}

std::string neighbourGeneratorTypeToJson(NeighbourGeneratorType type)
{
    auto it = NEIGHBOUR_GENERATOR_TYPE_TO_STRING.find(type);

    if (it != NEIGHBOUR_GENERATOR_TYPE_TO_STRING.end())
    {
        return it->second;
    }

    return NEIGHBOUR_GENERATOR_TYPE_TO_STRING.at(NeighbourGeneratorType::UNKNOWN);
}
