#include "IMutator.h"

IMutator::IMutator(std::mt19937& randGenerator, const ProblemData& problemData, double mutationProbability):
	_randGenerator(randGenerator),
	_problemData(problemData),
	_mutationProbability(mutationProbability)
{
	if (mutationProbability > 1.0 || mutationProbability < 0.0)
	{
		throw std::invalid_argument("Mutation probability is not in the range!");
	}
}
