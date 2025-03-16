#include "NeighbourGeneratorPrizeBest.h"

NeighbourGeneratorPrizeBest::NeighbourGeneratorPrizeBest(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem, int prizeSize) :
	INeighbourGenerator(mutators, problem),
	_prizeSize(prizeSize)
{
	if (prizeSize <= 0)
	{
		throw std::invalid_argument("Prize size must be a positive number");
	}
}

std::vector<CIndividual> NeighbourGeneratorPrizeBest::getNeighbours(int iteration, int numberOfNeighbours, CIndividual & currIndiv)
{
	int mutatorCount = _mutators.size();
	int baseNeighboursPerMutator = numberOfNeighbours / mutatorCount;
	int remainingNeighbours = numberOfNeighbours % mutatorCount;

	std::vector<CIndividual> allNeighbours;
	allNeighbours.reserve(numberOfNeighbours);

	int idx = 0;
	for (const std::shared_ptr<IMutator>& mut : _mutators)
	{
		int neighboursForThisMutator = baseNeighboursPerMutator;

		if (idx == _bestIdx)
		{
			neighboursForThisMutator += _prizeSize;
		}

		// loop is not needed as remainingNeighbours is always lower than mutators.size()
		if (remainingNeighbours > 0)
		{
			++neighboursForThisMutator;
			--remainingNeighbours;
		}

		std::vector<CIndividual> neighbours = currIndiv.createNeighbours(*mut, neighboursForThisMutator, _problem);

		allNeighbours.insert(allNeighbours.end(), neighbours.begin(), neighbours.end());

		++idx;
	}

	double bestRes = std::numeric_limits<double>::max();

	for (size_t i = 0; i < allNeighbours.size(); ++i)
	{
		if (allNeighbours[i].fitness().first < bestRes)
		{
			_bestIdx = i;
			bestRes = allNeighbours[i].fitness().first;
		}
	}

	if (bestRes > currIndiv.fitness().first)
	{
		_bestIdx = -1;
	}

	return allNeighbours;
}
