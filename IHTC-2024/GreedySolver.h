#pragma once

#include <queue>

#include"IHTCSolver.h"
#include "PatientWrapper.h"
#include "SurgeonOTInfo.h"
#include "SurgeryTimeActualToMax.h"
#include "OperatingTheaterWrapper.h"
#include "RoomBrokenAgeGender.h"
#include "RoomWithOccupancyRepresentation.h"
#include "ShiftNurses.h"

class GreedySolver : public IHTCSolver
{
public:
	GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator);
	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

private:
	std::string chooseNurse(
		ShiftNurses& shiftNurses,
		RoomWithOccupancyRepresentation& roomWithOccupancy,
		const std::vector<NurseDTO> nurses,
		const std::string& roomId
	) const;

	std::pair<int, std::string> chooseAdmissionDayAndOt(
		const IncomingPatientDTO& patient,
		std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
		std::unordered_map<std::string, SurgeryTimeActualToMax>& surgeons,
		std::vector<int>& dissallowedAdmissionDays
	) const;

	std::string chooseRoomId(
		const IncomingPatientDTO& patient,
		RoomWithOccupancyRepresentation& preprocessedRooms,
		int admissionDay
	) const;
};