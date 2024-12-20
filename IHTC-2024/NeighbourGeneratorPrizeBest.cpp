#include "NeighbourGeneratorPrizeBest.h"

NeighbourGeneratorPrizeBest::NeighbourGeneratorPrizeBest(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem, int prizeSize) :
	INeighbourGenerator(mutators, problem),
	prizeSize(prizeSize)
{
	if (prizeSize <= 0)
	{
		throw std::invalid_argument("Prize size must be a positive number");
	}
}

std::vector<CIndividual> NeighbourGeneratorPrizeBest::getNeighbours(int iteration, int numberOfNeighbours, CIndividual & currIndiv)
{
	int mutatorCount = mutators.size();
	int baseNeighboursPerMutator = numberOfNeighbours / mutatorCount;
	int remainingNeighbours = numberOfNeighbours % mutatorCount;

	std::vector<CIndividual> allNeighbours;
	allNeighbours.reserve(numberOfNeighbours);

	int idx = 0;
	for (const std::shared_ptr<IMutator>& mut : mutators)
	{
		int neighboursForThisMutator = baseNeighboursPerMutator;

		if (idx == bestIdx)
		{
			neighboursForThisMutator += prizeSize;
		}

		// loop is not needed as remainingNeighbours is always lower than mutators.size()
		if (remainingNeighbours > 0)
		{
			++neighboursForThisMutator;
			--remainingNeighbours;
		}

		std::vector<CIndividual> neighbours = currIndiv.createNeighbours(*mut, neighboursForThisMutator, problem);

		allNeighbours.insert(allNeighbours.end(), neighbours.begin(), neighbours.end());

		++idx;
	}

	double bestRes = std::numeric_limits<double>::max();

	for (size_t i = 0; i < allNeighbours.size(); ++i)
	{
		if (allNeighbours[i].getFitness().first < bestRes)
		{
			bestIdx = i;
			bestRes = allNeighbours[i].getFitness().first;
		}
	}

	if (bestRes > currIndiv.getFitness().first)
	{
		bestIdx = -1;
	}

	return allNeighbours;
}
