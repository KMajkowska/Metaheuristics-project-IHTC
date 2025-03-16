#pragma once

#include <functional>
#include <cmath>

#include "IHTCSolver.h"
#include "INeighbourGenerator.h"
#include "IStopCriterium.h"
#include "ICoolingScheme.h"
#include "TemperatureOperator.h"
#include "GenderGrouper.h"
#include "IHTCMutatorNurseRoomCover.h"

class SASolver : public IHTCSolver
{
public:
	SASolver(
		const ProblemData& problemData,
		double startingTemp,
		TemperatureOperator& tempOperator,
		std::mt19937& randGenerator,
		const IStopCriterium& stopCriterium,
		int neighbourhoodNumber,
		INeighbourGenerator& neighbourGenerator,
		ICIndividualConsumer& consumer,
		const GenderGrouper& genderGrouper,
		const IHTCMutatorNurseRoomCover& nurseRoomCover
	);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const override;

private:
	double startingTemp;
	const IStopCriterium& stopCriterium;
	TemperatureOperator& tempOperator;
	int neighbourhoodNumber;
	INeighbourGenerator& neighbourGenerator;
	const GenderGrouper& genderGrouper;
	const IHTCMutatorNurseRoomCover& nurseRoomCover;

	bool checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const;

	const double NORMALIZATION_DIVIDER = exp(1.0);
};