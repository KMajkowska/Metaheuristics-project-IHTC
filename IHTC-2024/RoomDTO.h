#pragma once

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" room is pretty similar, but we are separating json logic from algorithm logic
*/
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