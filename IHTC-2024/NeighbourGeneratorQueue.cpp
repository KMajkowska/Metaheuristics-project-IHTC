#include "NeighbourGeneratorQueue.h"

NeighbourGeneratorQueue::NeighbourGeneratorQueue(const std::vector<std::shared_ptr<IMutator>>& mutators, const IProblem& problem) :
	INeighbourGenerator(mutators, problem),
	mutatorQueue(std::deque<std::shared_ptr<IMutator>>(mutators.begin(), mutators.end()))
{}

std::vector<CIndividual> NeighbourGeneratorQueue::getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv)
{
	if (mutatorQueue.empty())
	{
		throw std::runtime_error("Mutator queue is empty.");
	}

	std::shared_ptr<IMutator> mut = mutatorQueue.front();

	mutatorQueue.pop();
	mutatorQueue.push(mut);

	return currIndiv.createNeighbours(
		*mut,
		numberOfNeigbours,
		problem
	);
}