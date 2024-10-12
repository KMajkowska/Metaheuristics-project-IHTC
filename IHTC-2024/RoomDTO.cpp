#include "RoomDTO.h"

std::string RoomDTO::getId() const
{
    return id;
}

int RoomDTO::getCapacity() const
{
    return capacity;
}

void to_json(nlohmann::json& j, const RoomDTO& room)
{
	j = nlohmann::json
	{
		{"id", room.getId()},
		{"capacity", room.getCapacity()}
	};
}
