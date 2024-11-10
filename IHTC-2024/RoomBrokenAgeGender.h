#pragma once

#include <string>
#include <compare>

struct RoomBrokenAgeGender
{
	RoomBrokenAgeGender(int brokenAge, int brokenGender, int brokenCapacity, const std::string& id);

	int brokenAge;
	int brokenGender;
	int brokenCapacity;

	std::string id;

	std::strong_ordering operator<=>(const RoomBrokenAgeGender& other) const;
};