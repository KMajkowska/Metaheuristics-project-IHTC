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

/**
 * @brief Pointer to have acces to neighbour generators
 * @param mutators mutator for generating
 * @param params what params from json we should use (e.g. how many neighbours we have)
 * @param problem what problem we are solving
 * @return 
*/
static std::unique_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
);
