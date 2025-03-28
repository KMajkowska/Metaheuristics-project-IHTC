#pragma once

#include <queue>

#include"IHTCSolver.h"
#include "PatientWrapper.h"
#include "SurgeonOTInfo.h"
#include "Workload.h"
#include "OperatingTheaterWrapper.h"
#include "RoomBrokenAgeGender.h"
#include "RoomWithOccupancyRepresentation.h"
#include "ShiftNurses.h"
#include "NurseWrapper.h"
#include "ICIndividualConsumer.h"

/**
 * @brief Greedy Solver for IHTC problem. Used for creating the starting individual for SASolver. Typical greedy algorithm
*/
class GreedySolver : public IHTCSolver
{
public:
	GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const override;

private:
	std::vector<std::string> chooseNurse(
		std::unordered_map<std::string, Workload>& nurseWorkloads,
		ShiftNurses& shiftNurses,
		RoomWithOccupancyRepresentation& roomWithOccupancy,
		const std::vector<NurseDTO> nurses,
		const std::string& roomId
	) const;

	std::pair<int, std::string> chooseAdmissionDayAndOt(
		const IncomingPatientDTO& patient,
		std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
		std::unordered_map<std::string, Workload>& surgeons,
		std::vector<int>& dissallowedAdmissionDays
	) const;

	std::string chooseRoomId(
		const IncomingPatientDTO& patient,
		RoomWithOccupancyRepresentation& preprocessedRooms,
		int admissionDay
	) const;
};