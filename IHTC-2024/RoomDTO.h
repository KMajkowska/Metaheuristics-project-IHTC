#pragma once

#include <string>
#include <nlohmann/json.hpp>

class RoomDTO
{
public:
	std::string getId() const;
	int getCapacity() const;

private:
	std::string id;
	int capacity;
};

void to_json(nlohmann::json& j, const RoomDTO& room);