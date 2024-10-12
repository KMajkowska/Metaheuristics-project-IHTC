#pragma once
#include<string>
#include<vector>

class SurgeonDTO
{
public:
	int getId();
	std::vector<int> getMaxSurgeryTime();
private:
	std::string id;
	std::vector<int> max_surgery_time;
};