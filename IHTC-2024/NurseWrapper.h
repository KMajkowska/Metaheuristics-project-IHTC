#pragma once

#include "WeightsDTO.h"
#include "NurseDTO.h"

class NurseWrapper
{
public:
	NurseWrapper(const WeightsDTO& weights, const NurseDTO& nurse, int day, const std::string& shiftType);

	auto operator<=>(const NurseWrapper& other) const;

	void addWorkload(int workload);
	void addSkillLevel(int skillLevel);

	const NurseDTO& nurse;

private:
	const WeightsDTO& weights;

	int maxWorkload;
	std::vector<int> usedWorkloads;

	std::vector<int> usedSkillLevels;

	int getWeightedRestriction() const;
};