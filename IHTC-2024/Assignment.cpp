#include "Assignment.h"

int Assignment::getDay() const
{
	return day;
}

void Assignment::setDay(int newDay)
{
	day = newDay;
}

std::string Assignment::getShift() const
{
	return shift;
}

void Assignment::setShift(const std::string& newShift)
{
	shift = newShift;
}

std::string Assignment::getRoomId() const
{
	return roomId;
}

void Assignment::setRoomId(const std::string& newRoomId)
{
	roomId = newRoomId;
}

void to_json(nlohmann::json& j, const Assignment& data)
{
	j = nlohmann::json
	{
		{"day", data.getDay()},
		{"shift", data.getShift()},
		{"room_id", data.getRoomId()},
	};
}

void from_json(const nlohmann::json& j, Assignment& data)
{
	data.setDay(j.at("day").get<int>());
	data.setShift(j.at("shift").get<std::string>());
	data.setRoomId(j.at("room_id").get<std::string>());
}
