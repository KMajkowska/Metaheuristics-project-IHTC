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

	std::strong_ordering operator<=>(const NurseWrapper&) const;

	void setNurse(NurseDTO&& nurse);
	NurseDTO nurse() const;

private:
	NurseDTO _nurse;
	WeightsDTO _weights;

	int _maxWorkload;

	std::vector<int> _usedWorkloads;
	std::vector<int> _usedSkillLevels;

	int getWeightedRestriction() const;

};