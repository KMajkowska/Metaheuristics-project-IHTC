#pragma once

#include <string>

struct RoomBrokenAgeGender
{
	RoomBrokenAgeGender(int brokenAge, int brokenGender, const std::string& id);

	int brokenAge;
	int brokenGender;

	std::string id;

	auto operator<=>(const RoomBrokenAgeGender& other);
};