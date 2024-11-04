#pragma once

#include <functional>
#include <cmath>

#include "IHTCSolver.h"

class SASolver : public IHTCSolver
{
public:
	SASolver(
		const ProblemData& problemData,
		double startingTemp, 
		std::function<double(double, double, int)> coolingFn, 
		std::mt19937& randGenerator, 
		std::function<bool(double, int)> stopCriterium, 
		int neighbourhoodNumber, 
		const IMutator& mutator
	);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

private:
	double startingTemp;
	std::function<double(double, double, int)> coolingFn;
	std::function<bool(double, int)> stopCriterium;
	int neighbourhoodNumber;
	const IMutator& mutator;

	bool checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const;
};