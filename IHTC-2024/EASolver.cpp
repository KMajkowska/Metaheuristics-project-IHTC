#include "EASolver.h"

EASolver::EASolver(
	const ProblemData& problemData,
	const ISelector& selector, 
	const IMutator& mutator, 
	const ICrosser& crosser, 
	std::mt19937& randGenerator, 
	Logger& logger
) :
	IHTCSolver(problemData, randGenerator, logger),
	selector(selector),
	mutator(mutator),
	crosser(crosser)
{}

CIndividual EASolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	return CIndividual();
}
