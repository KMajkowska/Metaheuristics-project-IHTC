#pragma once

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "SurgeonOTInfo.h"
#include <set>
#include "NurseWorkload.h"
#include<iostream>

ViolatedRestrictions getViolatedFromSolution(ProblemData& problemData, const SolutionData& solution);