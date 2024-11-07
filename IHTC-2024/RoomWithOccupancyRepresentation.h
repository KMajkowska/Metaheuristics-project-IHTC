#pragma once

#include "CIndividual.h"
#include "RoomInfo.h"
#include "IncomingPatientDTO.h"
#include "OccupantDTO.h"
#include "RoomDTO.h"

class RoomWithOccupancyRepresentation
{
public:
	RoomWithOccupancyRepresentation() = default;
	RoomWithOccupancyRepresentation(const std::vector<RoomDTO>& rooms, const std::vector<OccupantDTO>& occupants, const std::vector<IncomingPatientDTO>& patients, std::vector<std::string> shiftTypes, int days);
	RoomWithOccupancyRepresentation(const RoomWithOccupancyRepresentation& other) = default;

	void addIncomingPatient(int admissionDay, const std::string& roomId, const IncomingPatientDTO& patient);
	void addOccupant(const OccupantDTO& occupant);

	RoomInfo& getPatientRoomInfoRef(int day, const std::string& roomId);

	const std::unordered_map<std::string, RoomInfo>& getRoomsForGivenDayRef(int day);

private:

	void addPatient(int admissionDay, const std::string& roomId, const PatientDTO& patient, bool decreaseMaxCapacity);
	void addIncompatibleRoom(const IncomingPatientDTO& patient);

	std::vector<std::unordered_map<std::string, RoomInfo>> preprocessedRooms;

	std::vector<std::string> shiftTypes;
};