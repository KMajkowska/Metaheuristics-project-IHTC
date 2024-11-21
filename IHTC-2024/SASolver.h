#pragma once

#include <functional>
#include <cmath>

#include "IHTCSolver.h"
#include "INeighbourGenerator.h"
#include "IStopCriterium.h"
#include "ICoolingScheme.h"
#include "other.h"

class SASolver : public IHTCSolver
{
public:
	SASolver(
		const ProblemData& problemData,
		double startingTemp, 
		const ICoolingScheme& coolingScheme,
		std::mt19937& randGenerator, 
		const IStopCriterium& stopCriterium, 
		int neighbourhoodNumber, 
		INeighbourGenerator& neighbourGenerator, 
		Logger& logger
	);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

	std::string getCSVHeaders() const;

private:
	double startingTemp;
	const ICoolingScheme& coolingScheme;
	const IStopCriterium& stopCriterium;
	int neighbourhoodNumber;
	INeighbourGenerator& neighbourGenerator;

	bool checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const;

	const double NORMALIZATION_DIVIDER = exp(1.0);
};