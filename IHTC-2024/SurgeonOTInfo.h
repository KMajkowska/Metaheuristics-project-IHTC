#pragma once
#include <map>
#include <string>
#include "SurgeonsTime.h"

struct SurgeonOTInfo
{
	SurgeonOTInfo(int maxOTCapacity);
	SurgeonOTInfo() = default;

	bool isOTOvercrowded() const;

	int maxOTCapacity;
	std::map<std::string, SurgeonsTime> surgeonsOperations;
};
