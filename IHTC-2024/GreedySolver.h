#pragma once

#include <queue>

#include"IHTCSolver.h"
#include "PatientWrapper.h"
#include "RoomWrapper.h"
#include "SurgeonOTInfo.h"
#include "SurgeryTimeActualToMax.h"
#include "OperatingTheaterWrapper.h"

class GreedySolver : public IHTCSolver
{
public:
	GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator);
	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

private:
	void bestNextMove(CIndividual& individual);
	std::pair<int, std::string> chooseAdmissionDayAndOt(
		const IncomingPatientDTO& patient,
		std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
		std::unordered_map<std::string, SurgeryTimeActualToMax>& surgeons
	);
	std::string chooseRoomId(CIndividual& individual);
};