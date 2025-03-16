#pragma once

#include "SolverType.h"
#include "EASolver.h"
#include "params.h"
#include "RandomSolver.h"
#include "SASolver.h"
#include "GreedySolver.h"

/**
 * @brief Pointer to have acces to neighbour generators
 * @param problemData data from the problem
 * @param randGenerator 
 * @param params what params from json we should use (e.g. how many neighbours we have)
 * @return neighbour mutators
*/
std::vector<std::shared_ptr<IMutator>> getMutators(
	const ProblemData& problemData, 
	std::mt19937& randGenerator, 
	const Params& params
);

std::shared_ptr<IStopCriterium> getStopCriterium(const Params& params);

/**
 * @brief Pointer to create cooling scheme based on params
 * @param params what params we should use
 * @return 
*/
std::shared_ptr<ICoolingScheme> getCoolingScheme(const Params& params);

/**
 * @brief Pointer to have acces to neighbour generators
 * @param mutators mutator for generating
 * @param params what params from json we should use (e.g. how many neighbours we have)
 * @param problem what problem we are solving
 * @return neighbour generator
*/
std::shared_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
);
