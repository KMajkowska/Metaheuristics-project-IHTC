#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>

/**
 * @brief Class for storing info about rooms. What is current and max capacity of the rooms, how many genders is inside and how many age groups.
 * Moreover here is stored the list of patients, which are not allowed to stay in this room
 * Skill level of nurse required for this room on given shit is a maximum skill level of all sill levels from patients in this room. 
 * produced workload is summ of all patinets' workloads on given day and shift
 * there is also a list of occupants' ids (patient which are assign to this room from begging, not assigned during calculating solution)
*/
struct PatientRoomInfo
{
	PatientRoomInfo() = default;
	PatientRoomInfo(int maxCapacity, int currentCapacity) :
		_maxCapacity(maxCapacity),
		_currentCapacity(currentCapacity)
	{}

	std::unordered_map<std::string, int> _genders;
	int _maxCapacity;
	int _currentCapacity;
	std::unordered_map<std::string, int> _ageGroups;
	std::set<std::string> _unallowedPatients;
	std::unordered_map<std::string, std::vector<int>> _skillLevelsRequired;
	std::unordered_map<std::string, int> _shiftNameToProducedWorkload;
	std::set<std::string> _occupantIds;
};