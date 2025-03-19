#pragma once

#include "Patient.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "CIndividual.h"
#include "IProblem.h"
#include "solutionUtils.h"
#include "FitnessCalculator.h"

/*
macierz timeslot/pacjent
poczatkowo bedzie jakas lista kiedy jaki pacjent przyjety (miedzy release day i opcjonalnym due date)
potem bedzie heurystycznie sprawdzane, czy da si� go w ten dany dzien przypisac w odpowiedni dzien
 */

class IHTCProblem : public IProblem
{
public:
	IHTCProblem(
		const ProblemData& problemData, 
		std::function<ViolatedRestrictions(const ProblemData& problemData, const SolutionData& solution)> calculateRestrictions,
		const FitnessCalculator& calc
	);

	std::pair<double, ViolatedRestrictions> eval(const CIndividual& individual) const override;

protected:
	const ProblemData& _problemData;

	std::function<ViolatedRestrictions(const ProblemData& problemData, const SolutionData& solution)> calculateRestrictions;
	const FitnessCalculator& _calc;
};