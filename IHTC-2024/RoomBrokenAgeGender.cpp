#include "RoomBrokenAgeGender.h"

RoomBrokenAgeGender::RoomBrokenAgeGender(int brokenAge, int brokenGender, int brokenCapacity, const std::string& id) :
    brokenAge(brokenAge),
    brokenCapacity(brokenCapacity),
    brokenGender(brokenGender),
    id(id)
{}

std::strong_ordering RoomBrokenAgeGender::operator<=>(const RoomBrokenAgeGender& other) const
{ 
    if (auto cmp = brokenCapacity <=> other.brokenCapacity; cmp != 0) {
        return cmp;
    }

    if (auto cmp = brokenGender <=> other.brokenGender; cmp != 0) {
        return cmp;
    }

    return brokenAge <=> other.brokenAge;
}

