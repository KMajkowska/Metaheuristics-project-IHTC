#include "NurseDTO.h"

std::string NurseDTO::getId() const
{
    return id;
}

std::vector<ShiftDTO> NurseDTO::getWorkingShifts()
{
    return working_shifts;
}

int NurseDTO::getSkillLevel() const
{
    return skill_level;
}
