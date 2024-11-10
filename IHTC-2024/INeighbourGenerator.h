#pragma once

#include <vector>

#include "IMutator.h"

class INeighbourGenerator
{
public:
	INeighbourGenerator(const std::vector<IMutator>& mutators);

	virtual std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv) = 0;
};