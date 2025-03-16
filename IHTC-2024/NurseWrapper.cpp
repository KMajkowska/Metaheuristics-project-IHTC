#include "NurseWrapper.h"

NurseWrapper::NurseWrapper(const WeightsDTO& weights, const NurseDTO& nurse, int day, const std::string& shiftType) :
	_weights(weights),
	_nurse(nurse),
	_maxWorkload(nurse.getWorkloadByDayAndShift(day, shiftType))
{}

std::strong_ordering NurseWrapper::operator<=>(const NurseWrapper& other) const
{
	return getWeightedRestriction() <=> other.getWeightedRestriction();
}

void NurseWrapper::addWorkload(int workload)
{
	_usedWorkloads.push_back(workload);
}

void NurseWrapper::addSkillLevel(int skillLevel)
{
	_usedSkillLevels.push_back(skillLevel);
}

NurseDTO NurseWrapper::nurse() const
{
	return _nurse;
}

void NurseWrapper::setNurse(NurseDTO&& nurse)
{
	_nurse = std::move(nurse);
}

int NurseWrapper::getWeightedRestriction() const
{
	int sumOfWorkload = 0;
	int sumOfSkillLevelOverload = 0;

	for (const auto& skillLevel : _usedSkillLevels)
	{
		if (skillLevel > _nurse.skillLevel())
		{
			sumOfSkillLevelOverload += skillLevel - _nurse.skillLevel();
		}
	}

	for (const auto& workload : _usedWorkloads)
	{
		sumOfWorkload += workload;
	}

	sumOfWorkload = sumOfWorkload > _maxWorkload ? sumOfWorkload - _maxWorkload : 0;

	return _weights.getRoomNurseSkill() * sumOfSkillLevelOverload
		+ _weights.getNurseEccessiveWorkload() * sumOfWorkload;
}