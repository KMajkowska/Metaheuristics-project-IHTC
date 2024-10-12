#pragma once

#include <string>

class RoomDTO
{
public:
	std::string getId() const;
	int getCapacity() const;

	void setId(std::string newId);
	void setCapacity(int newCapacity);

private:
	std::string id;
	int capacity;
};