#include "IHTCProblem.h"
#include <iostream>

IHTCProblem::IHTCProblem(
	const ProblemData& problemData,
	std::function<ViolatedRestrictions(const ProblemData&, const SolutionData&)> calculateRestrictions, 
	std::function<double(const WeightsDTO&, const ViolatedRestrictions&)> evalFn,
	Logger& logger
) :
	problemData(problemData),
	calculateRestrictions(calculateRestrictions),
	evalFn(evalFn),
	logger(logger)
{}

double IHTCProblem::eval(const CIndividual& individual) const
{
	const auto& restrictions = calculateRestrictions(
		problemData,
		IHTCProblemIO::parseToSolution(individual, problemData)
	);

	const double res = evalFn(problemData.getWeights(), restrictions);

	logger.log(restrictions.getCSVData() + "," + std::to_string(res));

	return res;
}
