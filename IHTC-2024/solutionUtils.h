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

ViolatedRestrictions getViolatedFromSolution(const ProblemData& problemData, const SolutionData& solution);

double calculateFitness(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

double simplexCoolingScheme(double startingTemp, double currTemp, int iteration);

double gemanAndGemanCoolingScheme(double startingTemp, double currTemp, int iteration);

double variableCoolingFactorCoolingScheme(double startingTemp, double currTemp, int iteration, double maxIterationNumber);

std::vector<double> evaluateProblem(int amountOfRepetitions, const IProblem& problem, const ISolver& solver, const ISolver& initSolver);
