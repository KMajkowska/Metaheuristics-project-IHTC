#include "RoomWrapper.h"

RoomWrapper::RoomWrapper(const PatientRoomInfo& newRoom, const ProblemData& newProblemData, const std::string& roomId) :
	room(newRoom), 
	problemData(newProblemData),
	roomId(roomId)
{}

int RoomWrapper::operator<=>(const RoomWrapper& other) const
{
	if (room.currentCapacity != other.room.currentCapacity)
	{
		return room.currentCapacity > other.room.currentCapacity ? 1 : -1;
	}

	if (room.genders.size() != other.room.genders.size())
	{
		return room.genders.size() < other.room.genders.size() ? 1 : -1;
	}

	if (room.ageGroups.size() != other.room.ageGroups.size())
	{
		return room.ageGroups.size() < other.room.ageGroups.size() ? 1 : -1;
	}

	return 0;
}
