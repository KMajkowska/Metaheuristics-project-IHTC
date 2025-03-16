#pragma once

#include "SolverType.h"
#include "EASolver.h"
#include "params.h"
#include "RandomSolver.h"
#include "SASolver.h"
#include "GreedySolver.h"


std::vector<std::shared_ptr<IMutator>> getMutators(
	const ProblemData& problemData, 
	std::mt19937& randGenerator, 
	const Params& params
);

std::shared_ptr<IStopCriterium> getStopCriterium(const Params& params);

std::shared_ptr<ICoolingScheme> getCoolingScheme(const Params& params);

std::shared_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
);
