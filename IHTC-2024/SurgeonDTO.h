#pragma once

#include <string>
#include <vector>

class SurgeonDTO
{
public:
	std::string getId() const;
	std::vector<int> getMaxSurgeryTime();

	void setId(std::string newId);
	void setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime);

private:
	std::string id;
	std::vector<int> max_surgery_time;
};