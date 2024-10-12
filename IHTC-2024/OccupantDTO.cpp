#include "OccupantDTO.h"

std::string OccupantDTO::getRoomId() const
{
    return room_id;
}

void OccupantDTO::setRoomId(std::string newRoomId)
{
    room_id = newRoomId;
}
