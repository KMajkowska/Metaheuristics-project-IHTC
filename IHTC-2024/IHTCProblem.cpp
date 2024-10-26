#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(
	ProblemData& problemData,
	std::function<ViolatedRestrictions(ProblemData& problemData, const SolutionData& solution)> calculateRestrictions, 
	std::function<double(const WeightsDTO&, const ViolatedRestrictions&)> evalFn
) :
	problemData(problemData),
	calculateRestrictions(calculateRestrictions),
	evalFn(evalFn)
{}

double IHTCProblem::eval(const CIndividual& individual) const
{
	return evalFn(
		problemData.getWeights(), 
		calculateRestrictions(
			problemData, 
			IHTCProblemIO::parseToSolution(individual, problemData)
		)
	);
}
