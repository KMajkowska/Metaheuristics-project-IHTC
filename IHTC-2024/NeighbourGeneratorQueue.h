#pragma once

#include <queue>

#include "INeighbourGenerator.h"

class NeighbourGeneratorQueue : public INeighbourGenerator
{
public:
	NeighbourGeneratorQueue(const std::vector<std::shared_ptr<IMutator>>& mutators);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv);

private:
	std::queue<std::shared_ptr<IMutator>> mutatorQueue;
};