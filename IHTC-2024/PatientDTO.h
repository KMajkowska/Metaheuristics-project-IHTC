#pragma once
#include <string>
#include <vector>

class PatientDTO
{
	std::string getId() const;
	std::string getGender() const;
	std::string getAgeGroup() const;
	int getLengthOfStay() const;
	std::vector<int> getWorkloadProduced();
	std::vector<int> getSkillLevelRequired();

protected:
	std::string id;
	std::string gender;
	std::string age_group;
	int length_of_stay;
	std::vector<int> workload_produced;
	std::vector<int> skill_level_required;
};