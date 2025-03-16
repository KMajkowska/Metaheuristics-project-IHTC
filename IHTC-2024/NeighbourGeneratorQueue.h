#pragma once

#include <queue>

#include "INeighbourGenerator.h"

class NeighbourGeneratorQueue : public INeighbourGenerator
{
public:
	NeighbourGeneratorQueue(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv) override;

private:
	std::queue<std::shared_ptr<IMutator>> _mutatorQueue;
};