#include "INeighbourGenerator.h"

INeighbourGenerator::INeighbourGenerator(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem) :
	problem(problem),
	mutators(mutators)
{
	if (mutators.empty())
	{
		throw std::invalid_argument("Mutators list must contain at least one mutator");
	}
}
