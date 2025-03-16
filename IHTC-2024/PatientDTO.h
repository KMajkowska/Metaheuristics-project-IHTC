#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" patient is pretty similar, but we are separating json logic from algorithm logic
*/
class PatientDTO
{
public:
	std::string id() const;
	std::string gender() const;
	std::string ageGroup() const;
	int lengthOfStay() const;
	std::vector<int> workloadProduced() const;
	std::vector<int> skillLevelRequired() const;

	void setId(const std::string& newId);
	void setGender(const std::string& newGender);
	void setAgeGroup(const std::string& newAgeGroup);
	void setLengthOfStay(int newLengthOfStay);
	void setWorkloadProduced(std::vector<int> newWorkloadProduced);
	void setSkillLevelRequired(std::vector<int> newSkillLevelsRequired);

protected:
	std::string _id;
	std::string _gender;
	std::string _ageGroup;
	int _lengthOfStay;
	std::vector<int> _workloadProduced;
	std::vector<int> _skillLevelRequired;
};

void to_json(nlohmann::json& j, const PatientDTO& patient);
void from_json(const nlohmann::json& j, PatientDTO& patient);