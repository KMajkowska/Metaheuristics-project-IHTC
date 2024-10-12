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

void to_json(nlohmann::json& j, const NurseDTO& nurse)
{
	j = nlohmann::json
	{
		{"id", nurse.getId()},
		{"working_shifts", nurse.getWorkingShifts()},
		{"skill_level", nurse.getSkillLevel()}
	};
}
