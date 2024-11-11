#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(
	const ProblemData& problemData,
	std::function<ViolatedRestrictions(const ProblemData&, const SolutionData&)> calculateRestrictions, 
	std::function<double(const WeightsDTO&, const ViolatedRestrictions&)> evalFn
) :
	problemData(problemData),
	calculateRestrictions(calculateRestrictions),
	evalFn(evalFn)
{}

std::pair<double, ViolatedRestrictions> IHTCProblem::eval(const CIndividual& individual) const
{
	const auto restrictions = calculateRestrictions(
		problemData,
		IHTCProblemIO::parseToSolution(individual, problemData)
	);

	const double res = evalFn(problemData.getWeights(), restrictions);

	return std::make_pair(res, restrictions);
}
