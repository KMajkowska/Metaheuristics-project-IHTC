#include "EASolver.h"

EASolver::EASolver(
	ProblemData& problemData,
	const ISelector& selector, 
	const IMutator& mutator, 
	const ICrosser& crosser, 
	std::mt19937& randGenerator
) :
	IHTCSolver(problemData, randGenerator),
	selector(selector),
	mutator(mutator),
	crosser(crosser)
{}

CIndividual EASolver::solve(const IProblem & problem) const
{
	return CIndividual();
}
