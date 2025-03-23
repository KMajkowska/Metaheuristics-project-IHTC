#pragma once

#include <memory>

#include "ICIndividualConsumer.h"
#include "params.h"
#include "GreedySolverBuilder.h"
#include "RandomSolverBuilder.h"
#include "SASolverBuilder.h"

// only visible in this file
static std::mt19937 RANDOM_GENERATOR = createRandomGenerator();

std::shared_ptr<IHTCSolverBuilder> getSolverBuilder(
	SolverType solver,
	const Params& params,
	const ProblemData& problemData,
	ICIndividualConsumer& consumer,
	const IProblem& problem
);
