#include "INeighbourGenerator.h"

INeighbourGenerator::INeighbourGenerator(const std::vector<IMutator>& mutators)
{
	if (mutators.size() <= 0)
	{
		throw std::invalid_argument("Mutators list must contain at least one mutator");
	}
}
