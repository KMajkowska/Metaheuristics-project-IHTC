#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

struct PatientRoomInfo
{
	PatientRoomInfo(int maxCapacity, int currentCapacity) :
		maxCapacity(maxCapacity),
		currentCapacity(currentCapacity)
	{}

	std::unordered_map<std::string, int> genders;
	int maxCapacity;
	int currentCapacity;
	std::unordered_map<std::string, int> ageGroups;
	std::vector<std::string> unallowedPatients;
	std::unordered_map<std::string, int> skillLevelRequired;
	std::unordered_map<std::string, int> shiftNameToProducedWorkload;
};