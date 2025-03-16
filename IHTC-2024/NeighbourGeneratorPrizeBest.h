#pragma once

#include "INeighbourGenerator.h"

class NeighbourGeneratorPrizeBest : public INeighbourGenerator
{
public:
	NeighbourGeneratorPrizeBest(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem, int prizeSize);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv) override;

private:
	int _bestIdx { -1 };
	int _prizeSize { 0 };
};