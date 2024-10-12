#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class PatientDTO
{
public:
	std::string getId() const;
	std::string getGender() const;
	std::string getAgeGroup() const;
	int getLengthOfStay() const;
	std::vector<int> getWorkloadProduced() const;
	std::vector<int> getSkillLevelRequired() const;

	void setId(std::string newId);
	void setGender(std::string newGender);
	void setAgeGroup(std::string newAgeGroup);
	void setLengthOfStay(int newLengthOfStay);
	void setWorkloadProduced(std::vector<int> newWorkloadProduced);
	void setSkillLevelRequired(std::vector<int> newSkillLevelsRequired);

protected:
	std::string id;
	std::string gender;
	std::string age_group;
	int length_of_stay;
	std::vector<int> workload_produced;
	std::vector<int> skill_level_required;
};

void to_json(nlohmann::json& j, const PatientDTO& patient);