#include "EASolver.h"

EASolver::EASolver(const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator) :
	selector(selector),
	mutator(mutator),
	crosser(crosser),
	randGenerator(randGenerator)
{}

std::vector<CIndividual> EASolver::solve(const ProblemData & problemData, const Problem & problem) const
{
	return std::vector<CIndividual>();
}
