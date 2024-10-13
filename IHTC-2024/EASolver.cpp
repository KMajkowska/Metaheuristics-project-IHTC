#include "EASolver.h"

EASolver::EASolver(
	const ISelector& selector, 
	const IMutator& mutator, 
	const ICrosser& crosser, 
	std::mt19937& randGenerator
) :
	selector(selector),
	mutator(mutator),
	crosser(crosser),
	randGenerator(randGenerator)
{}

CIndividual EASolver::solve(const ProblemData & problemData, const IProblem & problem) const
{
	return CIndividual();
}
