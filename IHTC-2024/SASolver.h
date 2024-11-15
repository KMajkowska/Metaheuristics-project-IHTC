#pragma once

#include <functional>
#include <cmath>

#include "IHTCSolver.h"
#include "INeighbourGenerator.h"

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
		INeighbourGenerator& neighbourGenerator, 
		Logger& logger
	);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

	std::string getCSVHeaders() const;

private:
	double startingTemp;
	std::function<double(double, double, int)> coolingFn;
	std::function<bool(double, int)> stopCriterium;
	int neighbourhoodNumber;
	INeighbourGenerator& neighbourGenerator;

	bool checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const;

	const double NORMALIZATION_DIVIDER = exp(1.0);
};