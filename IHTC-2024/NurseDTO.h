#pragma once
#include<vector>
#include<string>
#include "ShiftDTO.h"

class NurseDTO
{
private:
	std::string id;
	std::vector<ShiftDTO> workins_shifts;
	int skill_level;
};