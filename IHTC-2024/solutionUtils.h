#pragma once

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"

static ViolatedRestrictions getViolatedFromSolution(ProblemData& problemData, const SolutionData& solution);