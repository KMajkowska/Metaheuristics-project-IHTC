#include "NurseDTO.h"

std::string NurseDTO::id() const
{
    return _id;
}

std::vector<ShiftDTO> NurseDTO::workingShifts() const
{
    return _workingShifts;
}

int NurseDTO::skillLevel() const
{
    return _skillLevel;
}

void NurseDTO::setId(const std::string& newId)
{
    _id = newId;
}

void NurseDTO::setWorkingShifts(std::vector<ShiftDTO> newWorkingShifts)
{
    _workingShifts = newWorkingShifts;
}

void NurseDTO::setSkillLevel(int newSkillLevel)
{
    _skillLevel = newSkillLevel;
}

int NurseDTO::getWorkloadByDayAndShift(int workingDay, std::string shiftStr) const
{
	for (const auto& shift : _workingShifts)
	{
		if (shift.day() == workingDay && shiftStr == shift.shift())
		{
			return shift.maxLoad();
		}
	}

	return 0;
}

std::vector<int> NurseDTO::workloadConverted(int days, const std::unordered_map<std::string, int> shiftNameToPos) const
{
	std::vector<int> workload(days * shiftNameToPos.size(), 0);

	for (const auto& shift : _workingShifts)
	{
		int iter = shift.day() + shiftNameToPos.at(shift.shift());

		workload[iter] = shift.maxLoad();
	}

	return workload;
}

void to_json(nlohmann::json& j, const NurseDTO& nurse)
{
	j = nlohmann::json
	{
		{"id", nurse.id()},
		{"working_shifts", nurse.workingShifts()},
		{"skill_level", nurse.skillLevel()}
	};
}

void from_json(const nlohmann::json& j, NurseDTO& nurse)
{
	nurse.setId(j.at("id").get<std::string>());
	nurse.setWorkingShifts(j.at("working_shifts").get<std::vector<ShiftDTO>>());
	nurse.setSkillLevel(j.at("skill_level").get<int>());

}
