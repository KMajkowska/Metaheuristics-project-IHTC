#include "RoomBrokenAgeGender.h"

RoomBrokenAgeGender::RoomBrokenAgeGender(int brokenAge, int brokenGender, int brokenCapacity, const std::string& id) :
    _brokenAge(brokenAge),
    _brokenCapacity(brokenCapacity),
    _brokenGender(brokenGender),
    _id(id)
{}

void RoomBrokenAgeGender::incrementBrokenAge()
{
    ++_brokenAge;
}

void RoomBrokenAgeGender::incrementBrokenGender()
{
    ++_brokenGender;
}

void RoomBrokenAgeGender::incrementBrokenCapacity()
{
    ++_brokenCapacity;
}

void RoomBrokenAgeGender::setId(const std::string& id)
{
    _id = id;
}

int RoomBrokenAgeGender::brokenAge() const
{
    return _brokenAge;
}

int RoomBrokenAgeGender::brokenGender() const
{
    return _brokenGender;
}

int RoomBrokenAgeGender::brokenCapacity() const
{
    return _brokenCapacity;
}

std::string RoomBrokenAgeGender::id() const
{
    return _id;
}

std::strong_ordering RoomBrokenAgeGender::operator<=>(const RoomBrokenAgeGender& other) const
{ 
    if (auto cmp = _brokenCapacity <=> other._brokenCapacity; cmp != 0) {
        return cmp;
    }

    if (auto cmp = _brokenGender <=> other._brokenGender; cmp != 0) {
        return cmp;
    }

    return _brokenAge <=> other._brokenAge;
}

