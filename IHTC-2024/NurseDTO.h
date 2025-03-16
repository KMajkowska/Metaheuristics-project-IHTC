#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "ShiftDTO.h"

/**
 * @brief DTO class to separte json data from data used to solve our problem. "Real" nurse is pretty similar, but we are separating json logic from algorithm logic
 * This class is used to take nurse from provided json file
*/
class NurseDTO
{
public:
	std::string id() const;
	std::vector<ShiftDTO> workingShifts() const;
	int skillLevel() const;

	void setId(const std::string& newId);
	void setWorkingShifts(std::vector<ShiftDTO> newWorkingShifts);
	void setSkillLevel(int newSkillLevel);

	int getWorkloadByDayAndShift(int workingDay, std::string shift) const;

	std::vector<int> workloadConverted(int day, const std::unordered_map<std::string, int> shiftNameToPos) const;

private:
	std::string _id;
	std::vector<ShiftDTO> _workingShifts;
	int _skillLevel { 0 };
};

void to_json(nlohmann::json& j, const NurseDTO& nurse);
void from_json(const nlohmann::json& j, NurseDTO& nurse);
