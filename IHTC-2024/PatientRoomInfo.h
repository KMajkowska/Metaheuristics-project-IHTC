#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>

struct PatientRoomInfo
{
	PatientRoomInfo() = default;
	PatientRoomInfo(int maxCapacity, int currentCapacity) :
		maxCapacity(maxCapacity),
		currentCapacity(currentCapacity)
	{}

	std::unordered_map<std::string, int> genders;
	int maxCapacity;
	int currentCapacity;
	std::unordered_map<std::string, int> ageGroups;
	std::set<std::string> unallowedPatients;
	std::unordered_map<std::string, std::vector<int>> skillLevelsRequired;
	std::unordered_map<std::string, int> shiftNameToProducedWorkload;
};