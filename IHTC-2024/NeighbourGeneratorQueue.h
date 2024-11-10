#pragma once

#include <vector>
#include <queue>

#include "INeighbourGenerator.h"

class NeighbourGeneratorQueue : public INeighbourGenerator
{
public:
	NeighbourGeneratorQueue(const std::vector<IMutator>& mutators);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv);

private:
	std::queue<IMutator> mutatorQueue;
};