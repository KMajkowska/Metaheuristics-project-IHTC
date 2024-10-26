#pragma once

#include <functional>

#include "IHTCSolver.h"

class SASolver : public IHTCSolver
{
public:
	SASolver(double startingTemp, const std::function<double(double, int)>& coolingFn, std::mt19937& randGenerator);

	CIndividual solve(const IProblem& problem) const;

private:
	double startingTemp;
	const std::function<double(double, int)>& coolingFn;
};