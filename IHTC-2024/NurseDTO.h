#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "ShiftDTO.h"

class NurseDTO
{
public:
	std::string getId() const;
	std::vector<ShiftDTO> getWorkingShifts() const;
	int getSkillLevel() const;

	void setId(std::string newId);
	void setWorkingShifts(std::vector<ShiftDTO> newWorkingShifts);
	void setSkillLevel(int newSkillLevel);

private:
	std::string id;
	std::vector<ShiftDTO> working_shifts;
	int skill_level;
};

void to_json(nlohmann::json& j, const NurseDTO& nurse);
