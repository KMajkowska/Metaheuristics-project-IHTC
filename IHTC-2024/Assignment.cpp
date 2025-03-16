#include "Assignment.h"

Assignment::Assignment() : Assignment(0, "", std::vector<std::string>())
{}

Assignment::Assignment(int day, std::string shift) : Assignment(day, shift, std::vector<std::string>())
{}

Assignment::Assignment(int day, std::string shift, std::vector<std::string> rooms) :
	_day(day),
	_shift(shift),
	_rooms(rooms)
{}

int Assignment::day() const
{
	return _day;
}

void Assignment::setDay(int newDay)
{
	_day = newDay;
}

std::string Assignment::shift() const
{
	return _shift;
}

void Assignment::setShift(const std::string& newShift)
{
	_shift = newShift;
}

std::vector<std::string> Assignment::rooms() const
{
	return _rooms;
}

void Assignment::setRooms(std::vector<std::string> newRooms)
{
	_rooms = newRooms;
}

void Assignment::appendRoom(const std::string& roomId)
{
	_rooms.push_back(roomId);
}

void to_json(nlohmann::json& j, const Assignment& data)
{
	j = nlohmann::json
	{
		{"day", data.day()},
		{"shift", data.shift()},
		{"rooms", data.rooms()},
	};
}

void from_json(const nlohmann::json& j, Assignment& data)
{
	data.setDay(j.at("day").get<int>());
	data.setShift(j.at("shift").get<std::string>());
	data.setRooms(j.at("rooms").get<std::vector<std::string>>());
}
