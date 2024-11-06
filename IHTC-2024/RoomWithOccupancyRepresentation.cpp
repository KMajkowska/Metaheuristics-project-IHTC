#include "RoomWithOccupancyRepresentation.h"


RoomWithOccupancyRepresentation::RoomWithOccupancyRepresentation(const std::vector<RoomDTO>& rooms, const std::vector<OccupantDTO>& occupants, const std::vector<IncomingPatientDTO>& patients, std::vector<std::string> shiftTypes, int days) :
	shiftTypes(shiftTypes)
{

	preprocessedRooms.reserve(days);

	for (int i = 0; i < days; ++i)
	{
		std::unordered_map<std::string, RoomInfo> newMap;
		newMap.reserve(days);

		preprocessedRooms.push_back(newMap);

		for (const auto& room : rooms)
		{
			preprocessedRooms[i][room.getId()] = RoomInfo(room.getCapacity(), room.getCapacity());
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
	addPatient(admissionDay, roomId, patient, false);
	addIncompatibleRoom(patient);
}

void RoomWithOccupancyRepresentation::addOccupant(const OccupantDTO& occupant)
{
	addPatient(0, occupant.getRoomId(), occupant, true);
}

RoomInfo& RoomWithOccupancyRepresentation::getPatientRoomInfoRef(int day, const std::string& roomId)
{
	return preprocessedRooms.at(day).at(roomId);
}

const std::unordered_map<std::string, RoomInfo>& RoomWithOccupancyRepresentation::getRoomsForGivenDayRef(int day)
{
	return preprocessedRooms.at(day);
}

void RoomWithOccupancyRepresentation::addPatient(int admissionDay, const std::string& roomId, const PatientDTO& patient, bool decreaseMaxCapacity)
{
	if (admissionDay < 0 || roomId.empty())
	{
		return;
	}

	for (int i = 0; i < patient.getLengthOfStay() && i + admissionDay < preprocessedRooms.size(); ++i)
	{
		auto& roomInfo = preprocessedRooms[i + admissionDay].at(roomId);

		roomInfo.occupantIds.insert(patient.getId());

		++roomInfo.ageGroups[patient.getAgeGroup()];
		++roomInfo.genders[patient.getGender()];

		--roomInfo.currentCapacity;

		if (decreaseMaxCapacity)
		{
			--roomInfo.maxCapacity;
		}

		for (int j = 0; j < shiftTypes.size(); ++j)
		{
			const auto& shiftType = shiftTypes[j];
			const auto& offset = i * shiftTypes.size() + j;

			roomInfo.skillLevelsRequired[shiftType].push_back(patient.getSkillLevelRequired()[offset]);
			roomInfo.shiftNameToProducedWorkload[shiftType] += patient.getWorkloadProduced()[offset];
		}

		if (!decreaseMaxCapacity)
		{
			roomInfo.patientIds.insert(patient.getId());
		}
	}
}

void RoomWithOccupancyRepresentation::addIncompatibleRoom(const IncomingPatientDTO& patient)
{
	for (const auto& incompatibleRoom : patient.getIncompatibleRoomIds())
	{
		for (int j = 0; j < preprocessedRooms.size(); ++j)
		{
			preprocessedRooms[j].at(incompatibleRoom).unallowedPatients.insert(patient.getId());
		}
	}
}
