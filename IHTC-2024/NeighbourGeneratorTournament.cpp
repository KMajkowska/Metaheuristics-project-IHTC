#include "NeighbourGeneratorTournament.h"

NeighbourGeneratorTournament::NeighbourGeneratorTournament(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem) :
	INeighbourGenerator(mutators, problem),
	mutators(mutators)
{}

std::vector<CIndividual> NeighbourGeneratorTournament::getNeighbours(int iteration, int numberOfNeighbours, CIndividual& currIndiv)
{

	if (mutators.empty())
	{
		throw std::runtime_error("Mutator list is empty.");
	}

	int mutatorCount = mutators.size();
	int baseNeighboursPerMutator = numberOfNeighbours / mutatorCount;
	int remainingNeighbours = numberOfNeighbours % mutatorCount;

	std::vector<CIndividual> allNeighbours;
	allNeighbours.reserve(numberOfNeighbours);

	for (const std::shared_ptr<IMutator>& mut : mutators)
	{
		int neighboursForThisMutator = baseNeighboursPerMutator;

		// loop is not needed as remainingNeighbours is always lower than mutators.size()
		if (remainingNeighbours > 0)
		{
			++neighboursForThisMutator;
			--remainingNeighbours;
		}

		std::vector<CIndividual> neighbours = currIndiv.createNeighbours(*mut, neighboursForThisMutator, problem);

		allNeighbours.insert(allNeighbours.end(), neighbours.begin(), neighbours.end());
	}

	return allNeighbours;
}