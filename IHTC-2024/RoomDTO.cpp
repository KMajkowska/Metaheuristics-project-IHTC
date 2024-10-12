#include "RoomDTO.h"

std::string RoomDTO::getId() const
{
    return id;
}

int RoomDTO::getCapacity() const
{
    return capacity;
}

void RoomDTO::setId(std::string newId)
{
    id = newId;
}

void RoomDTO::setCapacity(int newCapacity)
{
    capacity = newCapacity;
}
