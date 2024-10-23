#pragma once
#include <map>
#include <string>

struct SurgeonOTInfo
{
	SurgeonOTInfo(int maxOTCapacity);
	SurgeonOTInfo() = default;

	bool isOTOvercrowded() const;

	int maxOTCapacity;
	std::map<std::string, SurgeonsTime> surgeonsOperations;
};

struct SurgeonsTime
{
	int maxSurgeonCapacity = 0;
	int actualWorkingTime = 0;
};
