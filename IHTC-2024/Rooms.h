#pragma once
#include"Rooms.h"

class Rooms
{
public:
	std::string getId() const;
	int getCapacity() const;

	void setCapacity(int newCapacity);

private:
	std::string id;
	int capacity;
};