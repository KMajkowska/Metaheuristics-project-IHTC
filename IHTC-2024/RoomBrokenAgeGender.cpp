#include "RoomBrokenAgeGender.h"

RoomBrokenAgeGender::RoomBrokenAgeGender(int brokenAge, int brokenGender, const std::string& id) :
	brokenAge(brokenAge),
	brokenGender(brokenGender),
	id(id)
{}

auto RoomBrokenAgeGender::operator<=>(const RoomBrokenAgeGender& other)
{
	if (brokenGender != other.brokenGender)
	{
		return brokenGender < other.brokenGender ? 1 : -1;
	}

	if (brokenAge != other.brokenAge)
	{
		return brokenAge < other.brokenAge ? 1 : -1;
	}

	return 0;
}
