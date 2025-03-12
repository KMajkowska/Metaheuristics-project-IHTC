#pragma once

#include <queue>

#include "INeighbourGenerator.h"

/**
 * @brief Generator where mutatots are puy in the queue (randomly when creating code) and this generator use the mutator from appropriate index from queue
*/
class NeighbourGeneratorQueue : public INeighbourGenerator
{
public:
	NeighbourGeneratorQueue(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv);

private:
	std::queue<std::shared_ptr<IMutator>> mutatorQueue;
};