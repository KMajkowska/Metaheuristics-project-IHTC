#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(
	const ProblemData& problemData,
	std::function<ViolatedRestrictions(const ProblemData&, const SolutionData&)> calculateRestrictions, 
	const FitnessCalculator& calc
) :
	_problemData(problemData),
	calculateRestrictions(calculateRestrictions),
	_calc(calc)
{}

std::pair<double, ViolatedRestrictions> IHTCProblem::eval(const CIndividual& individual) const
{
	const auto restrictions = calculateRestrictions(_problemData, SolutionData(_problemData, individual));
	const double res = _calc.calculateFitnessWithWeight(_problemData.weights(), restrictions);

	return std::make_pair(res, restrictions);
}
