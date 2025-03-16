#include "RoomWithOccupancyRepresentation.h"

RoomWithOccupancyRepresentation::RoomWithOccupancyRepresentation(
	const std::vector<RoomDTO>& rooms, const std::vector<OccupantDTO>& occupants, 
	const std::vector<IncomingPatientDTO>& patients, 
	std::vector<std::string> shiftTypes,
	int days
) :
	_shiftTypes(shiftTypes)
{

	_preprocessedRooms.reserve(days);

	for (int i = 0; i < days; ++i)
	{
		std::unordered_map<std::string, RoomInfo> newMap;
		newMap.reserve(days);

		_preprocessedRooms.push_back(newMap);

		for (const auto& room : rooms)
		{
			_preprocessedRooms[i][room.id()] = RoomInfo(room.capacity(), room.capacity());
		}
	}

	for (const auto& occupant : occupants) 
	{
		addOccupant(occupant);
	}

	for (const auto& patient : patients)
	{
		addIncompatibleRoom(patient);
	}
}

void RoomWithOccupancyRepresentation::addIncomingPatient(int admissionDay, const std::string& roomId, const IncomingPatientDTO& patient)
{
	if (admissionDay < 0 || roomId.empty())
	{
		return;
	}

	for (int i = 0; i < patient.lengthOfStay() && i + admissionDay < _preprocessedRooms.size(); ++i)
	{
		auto& roomInfo { _preprocessedRooms[i + admissionDay].at(roomId) };

		roomInfo.patientIds().insert(patient.id());

		++roomInfo.ageGroups[patient.ageGroup()];
		++roomInfo.genders[patient.gender()];

		--roomInfo.currentCapacity;

		for (int j = 0; j < _shiftTypes.size(); ++j)
		{
			const auto& shiftType { _shiftTypes[j] };
			const auto& offset { i * _shiftTypes.size() + j };

			roomInfo.skillLevelsRequired[shiftType].push_back(patient.skillLevelRequired()[offset]);
			roomInfo.shiftNameToProducedWorkload[shiftType] += patient.workloadProduced()[offset];
		}
	}
	addIncompatibleRoom(patient);
}

void RoomWithOccupancyRepresentation::addOccupant(const OccupantDTO& occupant)
{

	for (int i = 0; i < occupant.lengthOfStay(); ++i)
	{
		auto& roomInfo { _preprocessedRooms[i].at(occupant.roomId()) };

		roomInfo.occupantIds.insert(occupant.id());

		++roomInfo.ageGroups[occupant.ageGroup()];
		++roomInfo.genders[occupant.gender()];

		--roomInfo.currentCapacity;
		--roomInfo.maxCapacity;
		
		for (int j = 0; j < _shiftTypes.size(); ++j)
		{
			const auto& shiftType { _shiftTypes[j] };
			const auto& offset { i * _shiftTypes.size() + j };

			roomInfo.skillLevelsRequired[shiftType].push_back(occupant.skillLevelRequired()[offset]);
			roomInfo.shiftNameToProducedWorkload[shiftType] += occupant.workloadProduced()[offset];
		}
	}
}

void RoomWithOccupancyRepresentation::addNurse(const NurseOutputDTO& nurse)
{
	for (const auto& assignment : nurse.assignments())
	{
		for (const auto& roomId : assignment.rooms())
		{
			addAssignment(assignment.day(), roomId, assignment.shift(), nurse.id());
		}
	}
}

void RoomWithOccupancyRepresentation::addAssignment(int day, const std::string& roomId, const std::string& shiftName, const std::string nurseId)
{
	patientRoomInfoRef(day, roomId).nurseIdToShift()[nurseId] = shiftName;
	patientRoomInfoRef(day, roomId).shiftToNurseId()[shiftName] = nurseId;
}

RoomInfo& RoomWithOccupancyRepresentation::patientRoomInfoRef(int day, const std::string& roomId)
{
	return _preprocessedRooms.at(day).at(roomId);
}

std::unordered_map<std::string, RoomInfo>& RoomWithOccupancyRepresentation::roomsForGivenDayRef(int day)
{
	return _preprocessedRooms.at(day);
}

void RoomWithOccupancyRepresentation::addIncompatibleRoom(const IncomingPatientDTO& patient)
{
	for (const auto& incompatibleRoom : patient.getIncompatibleRoomIds())
	{
		for (int j = 0; j < _preprocessedRooms.size(); ++j)
		{
			_preprocessedRooms[j].at(incompatibleRoom).unallowedPatients.insert(patient.id());
		}
	}
}
