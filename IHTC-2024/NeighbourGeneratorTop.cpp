#include "NeighbourGeneratorTop.h"

NeighbourGeneratorTop::NeighbourGeneratorTop(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem) :
	INeighbourGenerator(mutators, problem)
{}

std::vector<CIndividual> NeighbourGeneratorTop::getNeighbours(int iteration, int numberOfNeighbours, CIndividual & currIndiv)
{
	std::vector<CIndividual> allNeighbours;
	allNeighbours.reserve(numberOfNeighbours);

	while (allNeighbours.size() < numberOfNeighbours)
	{
		std::vector<CIndividual> currNeighbours;
		currNeighbours.reserve(_mutators.size() * PER_ITER);

		for (const auto& mut : _mutators)
		{
			std::vector<CIndividual> neighbours = currIndiv.createNeighbours(*mut, PER_ITER, _problem);

			currNeighbours.insert(currNeighbours.end(), neighbours.begin(), neighbours.end());
		}

		std::sort(currNeighbours.begin(), currNeighbours.end(),
			[](const CIndividual& a, const CIndividual& b) 
			{
				return std::less<>()(a.fitness().first, b.fitness().first);
			}
		);

		size_t halfSize = currNeighbours.size() / 2;

		allNeighbours.insert(allNeighbours.end(), currNeighbours.begin(), currNeighbours.begin() + halfSize);
	}

	return allNeighbours;
}
