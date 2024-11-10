#include "NeighbourGeneratorQueue.h"

NeighbourGeneratorQueue::NeighbourGeneratorQueue(const std::vector<IMutator>& mutators):
	INeighbourGenerator(mutators),
	mutatorQueue(std::deque<IMutator>(mutators.begin(), mutators.end()))
{}

std::vector<CIndividual> NeighbourGeneratorQueue::getNeighbours(int iteration, int numberOfNeigbours, const CIndividual& currIndiv) {
	if (mutatorQueue.empty()) 
	{
		throw std::runtime_error("Mutator queue is empty.");
	}

	const IMutator& mut = mutatorQueue.front();

	mutatorQueue.pop();
	mutatorQueue.push(mut);

	return currIndiv.createNeighbours(
		mut,
		numberOfNeigbours
	);
}