#pragma once

#include <string>
#include <vector>

class OperatingTheaterDTO
{
public:
	std::string getId() const;
	std::vector<int> getAvailability();
private:
	std::string id;
	std::vector<int> availability;
};