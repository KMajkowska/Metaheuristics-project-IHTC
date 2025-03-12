#pragma once

#include <vector>
#include <memory>

#include "IMutator.h"
#include "IProblem.h"

/**
 * @brief Class used as an interface to provide polymorphism for different ways of generating neighbours
*/
class INeighbourGenerator
{
public:
	INeighbourGenerator(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	virtual std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv) = 0;

protected:
	const std::vector<std::shared_ptr<IMutator>>& mutators;

	const IProblem& problem;
};