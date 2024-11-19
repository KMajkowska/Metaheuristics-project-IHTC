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
	const auto restrictions = calculateRestrictions(
		problemData,
		IHTCProblemIO::parseToSolution(individual, problemData)
	);

	const double res = calc.calculateFitnessWithWeight(problemData.getWeights(), restrictions);

	return std::make_pair(res, restrictions);
}
