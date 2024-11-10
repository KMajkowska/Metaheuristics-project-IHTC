#include "NurseDTO.h"

std::string NurseDTO::getId() const
{
    return id;
}

std::vector<ShiftDTO> NurseDTO::getWorkingShifts() const
{
    return working_shifts;
}

int NurseDTO::getSkillLevel() const
{
    return skill_level;
}

void NurseDTO::setId(const std::string& newId)
{
    id = newId;
}

void NurseDTO::setWorkingShifts(std::vector<ShiftDTO> newWorkingShifts)
{
    working_shifts = newWorkingShifts;
}

void NurseDTO::setSkillLevel(int newSkillLevel)
{
    skill_level = newSkillLevel;
}

int NurseDTO::getWorkloadByDayAndShift(int workingDay, std::string shiftStr) const
{
	for (const auto& shift : working_shifts)
	{
		if (shift.getDay() == workingDay && shiftStr == shift.getShift())
		{
			return shift.getMaxLoad();
		}
	}

	return 0;
}

std::vector<int> NurseDTO::getWorkloadConverted(int days, const std::unordered_map<std::string, int> shiftNameToPos) const
{
	std::vector<int> workload(days * shiftNameToPos.size(), 0);

	for (const auto& shift : working_shifts)
	{
		int iter = shift.getDay() + shiftNameToPos.at(shift.getShift());

		workload[iter] = shift.getMaxLoad();
	}

	return workload;
}

void to_json(nlohmann::json& j, const NurseDTO& nurse)
{
	j = nlohmann::json
	{
		{"id", nurse.getId()},
		{"working_shifts", nurse.getWorkingShifts()},
		{"skill_level", nurse.getSkillLevel()}
	};
}

void from_json(const nlohmann::json& j, NurseDTO& nurse)
{
	nurse.setId(j.at("id").get<std::string>());
	nurse.setWorkingShifts(j.at("working_shifts").get<std::vector<ShiftDTO>>());
	nurse.setSkillLevel(j.at("skill_level").get<int>());

}
