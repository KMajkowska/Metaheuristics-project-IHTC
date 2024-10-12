#pragma once

#include <string>
#include <vector>

class SurgeonDTO
{
public:
	std::string getId() const;
	std::vector<int> getMaxSurgeryTime();
private:
	std::string id;
	std::vector<int> max_surgery_time;
};