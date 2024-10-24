#pragma once

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "SurgeonOTInfo.h"
#include "NurseWorkload.h"

#include <set>

static ViolatedRestrictions getViolatedFromSolution(ProblemData& problemData, const SolutionData& solution);

static double calculateWeights(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

static double calculateNewTemp(double currTemp, int iteration);