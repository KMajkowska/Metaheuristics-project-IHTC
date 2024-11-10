#pragma once

#include "INeighbourGenerator.h"

class NeighbourGeneratorTournament : public INeighbourGenerator
{
public:
	NeighbourGeneratorTournament(const std::vector<std::shared_ptr<IMutator>>& mutators);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv);

private:
	std::vector<std::shared_ptr<IMutator>> mutators;
};