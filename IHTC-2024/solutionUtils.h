#pragma once

#include <set>
#include <iostream>

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "SurgeonOTInfo.h"
#include "NurseWorkload.h"
#include "IProblem.h"
#include "ISolver.h"
#include "RoomWithOccupancyRepresentation.h"
#include "PatientNurses.h"

ViolatedRestrictions getViolatedFromSolution(const ProblemData& problemData, const SolutionData& solution);

double calculateFitness(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

std::vector<std::pair<double, ViolatedRestrictions>> evaluateProblem(int amountOfRepetitions, const IProblem& problem, const ISolver& solver, const ISolver& initSolver);
