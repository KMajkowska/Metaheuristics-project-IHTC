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

double simplexCoolingScheme(double startingTemp, double currTemp, int iteration);

double gemanAndGemanCoolingScheme(double startingTemp, double currTemp, int iteration);

double variableCoolingFactorCoolingScheme(double startingTemp, double currTemp, int iteration, double maxIterationNumber);

std::vector<std::pair<double, ViolatedRestrictions>> evaluateProblem(int amountOfRepetitions, const IProblem& problem, const ISolver& solver, const ISolver& initSolver);

double calculateFitnessWithWeigtht(const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

bool stopCriteriumSA(double currTemp, int iteration);

bool stopCriteriumSAIter(double currTemp, int iteration);

double variableCoolingFactorCoolingSchemeParam(double startingTemp, double currTemp, int iteration);