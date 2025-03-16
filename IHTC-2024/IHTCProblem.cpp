#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(
	const ProblemData& problemData,
	std::function<ViolatedRestrictions(const ProblemData&, const SolutionData&)> calculateRestrictions, 
	const FitnessCalculator& calc
) :
	problemData(problemData),
	calculateRestrictions(calculateRestrictions),
	calc(calc)
{}

std::pair<double, ViolatedRestrictions> IHTCProblem::eval(const CIndividual& individual) const
{
	const auto restrictions = calculateRestrictions(problemData, SolutionData(problemData, individual));
	const double res = calc.calculateFitnessWithWeight(problemData.weights(), restrictions);

	return std::make_pair(res, restrictions);
}
