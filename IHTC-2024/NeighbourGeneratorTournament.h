#pragma once

#include "INeighbourGenerator.h"

/**
 * @brief Generator where we create neighbours in every mutator, choose the best ans then repeat as long as we reach the number of neighbours
*/
class NeighbourGeneratorTournament : public INeighbourGenerator
{
public:
	NeighbourGeneratorTournament(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv) override;

};