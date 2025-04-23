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
	* @brief It is problem, which exactly we are solving in this game - IHTC problem. It inhertis from iproblem, to provide polymorhipsm of problems
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