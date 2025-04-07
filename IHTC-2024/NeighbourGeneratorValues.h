#pragma once

#include "qstring.h"

enum class NeighbourGeneratorValues
{
    UKNOWN,
	PRIZE_BEST,
	QUEUE,
	TOP,
	TOURNAMENT
};

inline QString toString(NeighbourGeneratorValues level) {
    switch (level) {
    case NeighbourGeneratorValues::UKNOWN:
        return "<empty>";
    case NeighbourGeneratorValues::PRIZE_BEST:
        return "Prize best";
    case NeighbourGeneratorValues::QUEUE:
        return "Queue";
    case NeighbourGeneratorValues::TOP:
        return "Top";
    case NeighbourGeneratorValues::TOURNAMENT:
        return "Tournament";
    default:
        return "Unknown";
    }
}

inline const NeighbourGeneratorValues toEnumNeighbour(QString generator) {
    if (generator == "<empty>")
        return NeighbourGeneratorValues::UKNOWN;
    if (generator == "Prize best")
        return NeighbourGeneratorValues::PRIZE_BEST;
    if (generator == "Queue")
        return NeighbourGeneratorValues::QUEUE;
    if (generator == "Top")
        return NeighbourGeneratorValues::TOP;
    if (generator == "Tournament")
        return NeighbourGeneratorValues::TOURNAMENT;
    return
        NeighbourGeneratorValues();
}
