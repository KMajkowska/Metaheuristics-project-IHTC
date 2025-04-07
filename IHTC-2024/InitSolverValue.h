#pragma once
#include "Qstring.h"

enum class InitSolverValue
{
    UNKNOWN,
	RANDOM,
	GREEDY
};

inline QString toString(InitSolverValue level) {
    switch (level) {
    case InitSolverValue::UNKNOWN:
        return "<empty>";
    case InitSolverValue::RANDOM:
        return "Random";
    case InitSolverValue::GREEDY:
        return "Greedy";
    default:
        return "Unknown";
    }
}


inline const InitSolverValue toEnumValueInit(QString solver) {
    if (solver == "<empty>")
        return InitSolverValue::UNKNOWN;
    if (solver == "Random")
        return InitSolverValue::RANDOM;
    if (solver == "Greedy")
        return InitSolverValue::GREEDY;
    return
        InitSolverValue();
}