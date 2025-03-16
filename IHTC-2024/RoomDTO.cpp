#include "RoomDTO.h"

std::string RoomDTO::id() const
{
    return _id;
}

int RoomDTO::capacity() const
{
    return _capacity;
}

void RoomDTO::setId(const std::string& newId)
{
    _id = newId;
}

void RoomDTO::setCapacity(int newCapacity)
{
	_capacity = newCapacity;
}

void to_json(nlohmann::json & j, const RoomDTO & room)
{
	j = nlohmann::json
	{
		{"id", room.id()},
		{"capacity", room.capacity()}
	};
}

void from_json(const nlohmann::json& j, RoomDTO& room)
{
	room.setId(j.at("id").get<std::string>());
	room.setCapacity(j.at("capacity").get<int>());

}
