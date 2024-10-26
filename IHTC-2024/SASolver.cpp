#include "SASolver.h"

SASolver::SASolver(double startingTemp, const std::function<double(double, int)>& coolingFn, std::mt19937& randGenerator) :
	IHTCSolver(problemData, randGenerator),
	startingTemp(startingTemp),
	coolingFn(coolingFn)
{}

CIndividual SASolver::solve(const IProblem & problem) const
{
	return CIndividual();
}

