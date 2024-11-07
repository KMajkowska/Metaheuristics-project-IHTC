#include "RoomBrokenAgeGender.h"

RoomBrokenAgeGender::RoomBrokenAgeGender(int brokenAge, int brokenGender, const std::string& id) :
	brokenAge(brokenAge),
	brokenGender(brokenGender),
	id(id)
{}

std::strong_ordering RoomBrokenAgeGender::operator<=>(const RoomBrokenAgeGender& other) const
{ 
    if (auto cmp = brokenGender <=> other.brokenGender; cmp != 0) {
        return cmp;
    }

    return brokenAge <=> other.brokenAge;
}

