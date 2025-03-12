#pragma once

#include <functional>
#include <cmath>

#include "IHTCSolver.h"
#include "INeighbourGenerator.h"
#include "IStopCriterium.h"
#include "ICoolingScheme.h"
#include "other.h"
#include "TemperatureOperator.h"
#include "GenderGrouper.h"
#include "IHTCMutatorNurseRoomCover.h"

/**
 * @brief Solver for our Simulated Annealing. 
 * 
 * _problemData problem we are solving
 * _startingTemp Temperature we are starting our algorithm and which will we cool down
 * _stopCriterium Crietria which has to be met for algorithm to stop
 * _tempOperator operator which calculate out new temperature based on its criteria
 * _randGenerator generator for random operations
 * _neighbourhoodNumber number of generated neighbours for SA 
 * _neighbourGenerator class descirbing how to generate this neighbours
 * _logger logger for writing solutions in the console and in the excel files
 * _genderGrouper modification of SA algorithm, which modifies patients in the rooms to not broke as many gender restrictions
 * _nurseRoomCover modification of SA algorithm, which assing uncovered rooms for nurse
*/
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
		Logger& logger,
		const GenderGrouper& genderGrouper,
		const IHTCMutatorNurseRoomCover& nurseRoomCover
	);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

	std::string getCSVHeaders() const;

private:
	double _startingTemp;
	const IStopCriterium& _stopCriterium;
	TemperatureOperator& _tempOperator;
	int _neighbourhoodNumber;
	INeighbourGenerator& _neighbourGenerator;
	const GenderGrouper& _genderGrouper;
	const IHTCMutatorNurseRoomCover& _nurseRoomCover;

	bool checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const;

	void logResults(CIndividual& curr, CIndividual& best, double actualTemp, double worstNeighbour, double bestNeighbour, std::vector<double> fitnesses, std::string changerName) const;

	const double NORMALIZATION_DIVIDER = exp(1.0);
};