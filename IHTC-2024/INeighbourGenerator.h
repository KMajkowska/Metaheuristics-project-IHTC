#pragma once

#include <vector>
#include <memory>

#include "IMutator.h"

class INeighbourGenerator
{
public:
	INeighbourGenerator(const std::vector<std::shared_ptr<IMutator>>& mutators);

	virtual std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv) = 0;
};