#pragma once

#include "Patient.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "ViolatedRestrictions.h"
#include "CIndividual.h"
#include "IProblem.h"
#include "IHTCProblemIO.h"
#include "solutionUtils.h"

/*
	macierz timeslot/pacjent
	poczatkowo bedzie jakas lista kiedy jaki pacjent przyjety (miedzy release day i opcjonalnym due date)
	potem bedzie heurystycznie sprawdzane, czy da si� go w ten dany dzien przypisac w odpowiedni dzien
 */

class IHTCProblem : public IProblem
{
public:
	IHTCProblem(
		ProblemData& problemData, 
		std::function<ViolatedRestrictions(ProblemData& problemData, const SolutionData& solution)> calculateRestrictions,
		std::function<double(const WeightsDTO&, const ViolatedRestrictions&)> evalFn);

	double eval(const CIndividual& individual) const;

protected:
	ProblemData& problemData;

	std::function<ViolatedRestrictions(ProblemData& problemData, const SolutionData& solution)> calculateRestrictions;
	std::function<double(const WeightsDTO&, const ViolatedRestrictions&)> evalFn;
};