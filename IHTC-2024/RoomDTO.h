#pragma once

#include <string>
#include <nlohmann/json.hpp>

class RoomDTO
{
public:
	std::string id() const;
	int capacity() const;

	void setId(const std::string& newId);
	void setCapacity(int newCapacity);

private:
	std::string _id;
	int _capacity;
};

void to_json(nlohmann::json& j, const RoomDTO& room);
void from_json(const nlohmann::json& j, RoomDTO& room);