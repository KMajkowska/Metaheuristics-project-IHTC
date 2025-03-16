#pragma once

#include "SolverType.h"
#include "EASolver.h"
#include "params.h"
#include "RandomSolver.h"
#include "SASolver.h"
#include "GreedySolver.h"
#include "consts.h"


//static  std::unique_ptr<IHTCSolver> getSolver(
//	ICIndividualConsumer& consumer, 
//	const Params& params, 
//	const ProblemData& problemData
//);

static std::unique_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
);
