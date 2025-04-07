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

std::mt19937 createRandomGenerator()
{
	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	std::mt19937 mt(seed);

	return mt;
}