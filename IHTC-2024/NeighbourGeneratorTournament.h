#pragma once

#include "INeighbourGenerator.h"

class NeighbourGeneratorTournament : public INeighbourGenerator
{
public:
	NeighbourGeneratorTournament(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv);

private:
	std::vector<std::shared_ptr<IMutator>> mutators;
};