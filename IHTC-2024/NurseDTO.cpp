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

void NurseDTO::setId(std::string newId)
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