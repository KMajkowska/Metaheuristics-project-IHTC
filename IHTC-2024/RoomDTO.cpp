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

void to_json(nlohmann::json & j, const RoomDTO & room)
{
	j = nlohmann::json
	{
		{"id", room.getId()},
		{"capacity", room.getCapacity()}
	};
}

void from_json(const nlohmann::json& j, RoomDTO& room)
{
	room.setId(j.at("id").get<std::string>());
	room.setCapacity(j.at("capacity").get<int>());

}
