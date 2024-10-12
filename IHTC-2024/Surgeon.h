#pragma once
#include<string>
#include<vector>

class Surgeon
{
public:
	std::string getId() const;
	std::vector<int> getMaxSurgeryTime() const;

	void setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime);

private:
	std::string id;
	std::vector<int> max_surgery_time;
};