#pragma once
#include <map>
#include <string>
#include "SurgeonsTime.h"

/**
 * @brief Class where we check if OT is overcrowded so if assign surgeries last longer than this OT is open on given day 
*/
struct SurgeonOTInfo
{
	SurgeonOTInfo(int maxOTCapacity);
	SurgeonOTInfo() = default;

	bool isOTOvercrowded() const;

	int maxOTCapacity;
	std::map<std::string, SurgeonsTime> surgeonsOperations;
};
