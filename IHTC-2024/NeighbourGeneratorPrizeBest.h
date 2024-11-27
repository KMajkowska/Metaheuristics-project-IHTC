#pragma once

#include "INeighbourGenerator.h"

class NeighbourGeneratorPrizeBest : public INeighbourGenerator
{
public:
	NeighbourGeneratorPrizeBest(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem, int prizeSize);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv);

private:
	int bestIdx = -1;
	int prizeSize;
};