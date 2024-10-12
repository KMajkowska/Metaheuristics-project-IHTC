#pragma once

#include <string>

class RoomDTO
{
public:
	std::string getId() const;
	int getCapacity() const;

private:
	std::string id;
	int capacity;
};