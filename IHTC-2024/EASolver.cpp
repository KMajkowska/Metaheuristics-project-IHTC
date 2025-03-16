#include "EASolver.h"

EASolver::EASolver(
	const ProblemData& problemData,
	const ISelector& selector, 
	const IMutator& mutator, 
	const ICrosser& crosser, 
	std::mt19937& randGenerator, 
	ICIndividualConsumer& consumer
) :
	IHTCSolver(problemData, randGenerator, consumer),
	_selector(selector),
	_mutator(mutator),
	_crosser(crosser)
{}

CIndividual EASolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	return CIndividual();
}
