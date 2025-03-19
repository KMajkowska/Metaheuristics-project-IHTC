#pragma once

#include "INeighbourGenerator.h"

/**
 * @brief Generator where the mutator which generate the best individual in previous iteration now has more individuals to generate
*/
class NeighbourGeneratorPrizeBest : public INeighbourGenerator
{
public:
	NeighbourGeneratorPrizeBest(const std::vector<std::shared_ptr<IMutator>> mutators, const IProblem& problem, int prizeSize);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv) override;

private:
	int _bestIdx { -1 };
	int _prizeSize { 0 };
};