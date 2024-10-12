#pragma once
#include<string>
#include<vector>

class OperatingTheaterDTO
{
public:
	int getId();
	std::vector<int> getAvailability;
private:
	std::string id;
	std::vector<int> availability;
};