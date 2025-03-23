#include "solverBuilderUtils.h"

std::shared_ptr<IHTCSolverBuilder> getSolverBuilder(
	SolverType solver,
	const Params& params,
	const ProblemData& problemData,
	ICIndividualConsumer& consumer,
	const IProblem& problem
)
{
	switch (solver) {
	case SolverType::GREEDY:
		return std::make_shared<GreedySolverBuilder>(problemData, RANDOM_GENERATOR, consumer);
	case SolverType::RAND:
		return std::make_shared<RandomSolverBuilder>(problemData, RANDOM_GENERATOR, consumer);
	case SolverType::SA:
		return std::make_shared<SASolverBuilder>(params, problemData, RANDOM_GENERATOR, consumer, problem);
	default:
		throw std::invalid_argument("Incorrect solver builder");
	}
}