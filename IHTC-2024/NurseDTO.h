#pragma once

#include <vector>
#include <string>

#include "ShiftDTO.h"

class NurseDTO
{
public:
	std::string getId() const;
	std::vector<ShiftDTO> getWorkingShifts();
	int getSkillLevel() const;

private:
	std::string id;
	std::vector<ShiftDTO> working_shifts;
	int skill_level;
};