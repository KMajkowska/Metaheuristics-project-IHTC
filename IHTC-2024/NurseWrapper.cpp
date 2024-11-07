#include "NurseWrapper.h"

NurseWrapper::NurseWrapper(const WeightsDTO& weights, const NurseDTO& nurse, int day, const std::string& shiftType) :
	weights(weights),
	nurse(nurse),
	maxWorkload(nurse.getWorkloadByDayAndShift(day, shiftType))
{}

std::strong_ordering NurseWrapper::operator<=>(const NurseWrapper& other) const
{
	return getWeightedRestriction() <=> other.getWeightedRestriction();
}

void NurseWrapper::addWorkload(int workload)
{
	usedWorkloads.push_back(workload);
}

void NurseWrapper::addSkillLevel(int skillLevel)
{
	usedSkillLevels.push_back(skillLevel);
}

int NurseWrapper::getWeightedRestriction() const
{
	int sumOfWorkload = 0;
	int sumOfSkillLevelOverload = 0;

	for (const auto& skillLevel : usedSkillLevels)
	{
		if (skillLevel > nurse.getSkillLevel())
		{
			sumOfSkillLevelOverload += skillLevel - nurse.getSkillLevel();
		}
	}

	for (const auto& workload : usedWorkloads)
	{
		sumOfWorkload += workload;
	}

	sumOfWorkload = sumOfWorkload > maxWorkload ? sumOfWorkload - maxWorkload : 0;

	return weights.getRoomNurseSkill() * sumOfSkillLevelOverload
		+ weights.getNurseEccessiveWorkload() * sumOfWorkload;
}