#pragma once
#include<string>
#include<vector>

class OperatingTheater
{
public:
	std::string getId() const;
	std::vector<int> getAvailability() const;

	void setAvailability(std::vector<int> newAvailabilty);

private:
	std::string id;
	std::vector<int> availability;
};