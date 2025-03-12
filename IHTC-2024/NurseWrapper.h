#pragma once

#include <compare>

#include "WeightsDTO.h"
#include "NurseDTO.h"

/**
 * @brief Wrapper for nurse class to allow us to compare two nurses and use this to choose, which nurse is better to assign when we modify our solution
*/
class NurseWrapper
{
public:
	NurseWrapper(const WeightsDTO& weights, const NurseDTO& nurse, int day, const std::string& shiftType);

	void addWorkload(int workload);
	void addSkillLevel(int skillLevel);

	NurseDTO nurse;

	std::strong_ordering operator<=>(const NurseWrapper&) const;

private:
	int getWeightedRestriction() const;

	WeightsDTO weights;

	int maxWorkload;
	std::vector<int> usedWorkloads;

	std::vector<int> usedSkillLevels;
};