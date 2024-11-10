#include "NeighbourGeneratorTournament.h"

MutatorOrchestratorTournament::MutatorOrchestratorTournament(const std::vector<IMutator>& mutators) :
	INeighbourGenerator(mutators),
	mutators(mutators)
{}

std::vector<CIndividual> MutatorOrchestratorTournament::getNeighbours(int iteration, int numberOfNeighbours, const CIndividual & currIndiv)
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

    for (const IMutator& mut : mutators) 
    {
        int neighboursForThisMutator = baseNeighboursPerMutator;
        
        // loop is not needed as remainingNeighbours is always lower thamn mutators.size()
        if (remainingNeighbours > 0)
        {
            ++neighboursForThisMutator;
            --remainingNeighbours;
        }

        std::vector<CIndividual> neighbours = currIndiv.createNeighbours(mut, neighboursForThisMutator);

        allNeighbours.insert(allNeighbours.end(), neighbours.begin(), neighbours.end());
    }

    return allNeighbours;
}
