#pragma once

#include "INeighbourGenerator.h"

/**
 * @brief Generator where the generated neighbours are the half of the total neighbours for next iteration. Neighbours are chooses as the elite from generated neighbours
*/
class NeighbourGeneratorTop : public INeighbourGenerator
{
public:
	NeighbourGeneratorTop(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem);

	std::vector<CIndividual> getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv) override;

private:
	static constexpr int PER_ITER = 1;
};