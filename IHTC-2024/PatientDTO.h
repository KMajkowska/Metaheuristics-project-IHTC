#pragma once
#include <string>
#include <vector>

class PatientDTO
{
protected:
	std::string id;
	std::string gender;
	std::string age_group;
	int length_of_stay;
	std::vector<int> workload_produced;
	std::vector<int> skill_level_required;
};