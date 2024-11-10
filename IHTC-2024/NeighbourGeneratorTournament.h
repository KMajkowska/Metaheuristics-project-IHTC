#pragma once

#include "INeighbourGenerator.h"

class MutatorOrchestratorTournament : public INeighbourGenerator
{
public:
	MutatorOrchestratorTournament(const std::vector<IMutator>& mutators);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv);

private:
	const std::vector<IMutator>& mutators;
};