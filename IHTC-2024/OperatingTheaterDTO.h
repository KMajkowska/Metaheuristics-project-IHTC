#pragma once

#include <string>
#include <vector>

class OperatingTheaterDTO
{
public:
	std::string getId() const;
	std::vector<int> getAvailability() const;

	void setId(std::string newId);
	void setAvailability(std::vector<int> newAvailabilty);

private:
	std::string id;
	std::vector<int> availability;
};