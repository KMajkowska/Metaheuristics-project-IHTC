#pragma once

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "SurgeonOTInfo.h"
#include "NurseWorkload.h"

#include <set>

ViolatedRestrictions getViolatedFromSolution(ProblemData& problemData, const SolutionData& solution);