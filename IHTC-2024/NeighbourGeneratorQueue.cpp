#include "NeighbourGeneratorQueue.h"

NeighbourGeneratorQueue::NeighbourGeneratorQueue(const std::vector<std::shared_ptr<IMutator>> mutators, const IProblem& problem) :
	INeighbourGenerator(mutators, problem),
	_mutatorQueue(std::deque<std::shared_ptr<IMutator>>(mutators.begin(), mutators.end()))
{}

std::vector<CIndividual> NeighbourGeneratorQueue::getNeighbours(int iteration, int numberOfNeigbours, CIndividual& currIndiv)
{
	std::shared_ptr<IMutator> mut = _mutatorQueue.front();

	_mutatorQueue.pop();
	_mutatorQueue.push(mut);

	return currIndiv.createNeighbours(
		*mut,
		numberOfNeigbours,
		_problem
	);
}