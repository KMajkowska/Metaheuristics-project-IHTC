#pragma once

#include "CIndividual.h"
#include "RoomInfo.h"
#include "IncomingPatientDTO.h"
#include "OccupantDTO.h"
#include "RoomDTO.h"
#include "NurseOutputDTO.h"

/**
 * @brief Class representing a actual room, with occupants and adding patiends. Here we also add nurses and their assignemnts (linked to this room). 

*/
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

	/**
	 * @brief Returns the RoomInfo about the given room on given day
	 * @param day which day we want to return
	 * @param roomId which room we want to return
	 * @return info about the room
	*/
	RoomInfo& getPatientRoomInfoRef(int day, const std::string& roomId);

	const std::unordered_map<std::string, RoomInfo>& getRoomsForGivenDayRef(int day);

private:
	void addIncompatibleRoom(const IncomingPatientDTO& patient);

	std::vector<std::unordered_map<std::string, RoomInfo>> preprocessedRooms;

	std::vector<std::string> shiftTypes;
};