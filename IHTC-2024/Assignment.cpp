#include "Assignment.h"

Assignment::Assignment() : Assignment(0, "", std::vector<std::string>())
{}

Assignment::Assignment(int day, std::string shift) : Assignment(day, shift, std::vector<std::string>())
{}

Assignment::Assignment(int day, std::string shift, std::vector<std::string> rooms) :
	day(day),
	shift(shift),
	rooms(rooms)
{}

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

std::vector<std::string> Assignment::getRooms() const
{
	return rooms;
}

void Assignment::setRooms(std::vector<std::string> newRooms)
{
	rooms = newRooms;
}

void Assignment::appendRoom(const std::string& roomId)
{
	rooms.push_back(roomId);
}

void to_json(nlohmann::json& j, const Assignment& data)
{
	j = nlohmann::json
	{
		{"day", data.getDay()},
		{"shift", data.getShift()},
		{"rooms", data.getRooms()},
	};
}

void from_json(const nlohmann::json& j, Assignment& data)
{
	data.setDay(j.at("day").get<int>());
	data.setShift(j.at("shift").get<std::string>());
	data.setRooms(j.at("rooms").get<std::vector<std::string>>());
}
