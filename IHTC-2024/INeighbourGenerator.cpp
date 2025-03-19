#include "INeighbourGenerator.h"

INeighbourGenerator::INeighbourGenerator(const std::vector<std::shared_ptr<IMutator>> mutators, const IProblem& problem) :
	_problem(problem),
	_mutators(mutators)
{
	if (mutators.empty())
	{
		throw std::invalid_argument("Mutators list must contain at least one mutator");
	}
}
