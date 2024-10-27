#pragma once

#include <set>

#include "ViolatedRestrictions.h"
#include "SolutionData.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "SurgeonOTInfo.h"
#include "NurseWorkload.h"
#include "IProblem.h"
#include "ISolver.h"

ViolatedRestrictions getViolatedFromSolution(const ProblemData& problemData, const SolutionData& solution);

double calculateFitness(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

double calculateNewTemp(double currTemp, int iteration);

std::vector<double> evaluateProblem(int amountOfRepetitions, const IProblem& problem, const ISolver& solverm, const CIndividual& startingIndividual );
