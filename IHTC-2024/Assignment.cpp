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

std::string Assignment::getRoom() const
{
	return roomId;
}

void Assignment::setRoomId(const std::string& newRoomId)
{
	roomId = newRoomId;
}