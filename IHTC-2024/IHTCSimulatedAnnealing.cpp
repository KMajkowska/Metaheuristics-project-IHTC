#include "IHTCSimulatedAnnealing.h"

IHTCSimulatedAnnealing::IHTCSimulatedAnnealing(
	ProblemData& problemData, 
	double startingTemp,
	const std::function<double(double, int)>& coolingFn,
	const std::function<double(const WeightsDTO&, const ViolatedRestrictions&)>& eval
) :
	IHTCProblem(problemData, eval),
	startingTemp(startingTemp),
	coolingFn(coolingFn)
{}

CIndividual IHTCSimulatedAnnealing::solve(CIndividual startingIndividual) const
{
	return CIndividual();
}
