#include "NeighbourGeneratorTournament.h"

NeighbourGeneratorTournament::NeighbourGeneratorTournament(const std::vector<std::shared_ptr<IMutator>> mutators, const IProblem& problem) :
	INeighbourGenerator(mutators, problem)
{}

std::vector<CIndividual> NeighbourGeneratorTournament::getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv)
{
	auto mutatorCount { _mutators.size() };
	auto baseNeighboursPerMutator { numberOfNeighbours / mutatorCount };
	auto remainingNeighbours { numberOfNeighbours % mutatorCount };

	std::vector<CIndividual> allNeighbours;
	allNeighbours.reserve(numberOfNeighbours);

	for (const std::shared_ptr<IMutator>& mut : _mutators)
	{
		int neighboursForThisMutator = baseNeighboursPerMutator;

		// loop is not needed as remainingNeighbours is always lower than mutators.size()
		if (remainingNeighbours > 0)
		{
			++neighboursForThisMutator;
			--remainingNeighbours;
		}

		std::vector<CIndividual> neighbours { currIndiv.createNeighbours(*mut, neighboursForThisMutator, _problem) };

		allNeighbours.insert(allNeighbours.end(), neighbours.begin(), neighbours.end());
	}

	return allNeighbours;
}