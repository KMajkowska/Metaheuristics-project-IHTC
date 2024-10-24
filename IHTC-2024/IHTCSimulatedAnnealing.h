#pragma once

#include <functional>

#include "IHTCProblem.h"

class IHTCSimulatedAnnealing : public IHTCProblem
{
public:
	IHTCSimulatedAnnealing(
		ProblemData& problemData,
		double startingTemp, 
		const std::function<double(double, int)>& coolingFn, 
		const std::function<double(const WeightsDTO&, const ViolatedRestrictions&)>& eval
	);

	CIndividual solve(CIndividual startingIndividual) const;

private:
	double startingTemp;
	const std::function<double(double, int)>& coolingFn;
};