#pragma once

#include "CIndividual.h"
#include "RoomInfo.h"
#include "IncomingPatientDTO.h"
#include "OccupantDTO.h"
#include "RoomDTO.h"
#include "NurseOutputDTO.h"

class RoomWithOccupancyRepresentation
{
public:
	RoomWithOccupancyRepresentation() = default;
	RoomWithOccupancyRepresentation(const std::vector<RoomDTO>& rooms, const std::vector<OccupantDTO>& occupants, const std::vector<IncomingPatientDTO>& patients, std::vector<std::string> shiftTypes, int days);
	RoomWithOccupancyRepresentation(const RoomWithOccupancyRepresentation& other) = default;

	void addIncomingPatient(int admissionDay, const std::string& roomId, const IncomingPatientDTO& patient);
	void addOccupant(const OccupantDTO& occupant);

	void addNurse(const NurseOutputDTO& nurse);
	void addAssignment(int day, const std::string& roomId, const std::string& shiftName, const std::string nurseId);

	RoomInfo& patientRoomInfoRef(int day, const std::string& roomId);

	std::unordered_map<std::string, RoomInfo>& roomsForGivenDayRef(int day);

private:
	void addIncompatibleRoom(const IncomingPatientDTO& patient);

	std::vector<std::unordered_map<std::string, RoomInfo>> _preprocessedRooms;

	std::vector<std::string> _shiftTypes;
};