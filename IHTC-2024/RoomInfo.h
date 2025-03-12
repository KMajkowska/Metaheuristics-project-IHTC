#pragma once

#include "PatientRoomInfo.h"

#include <set>

/**
 * @brief Extension of PatientRoomInfo, where we also store id of nurse in given day and shift, list of patientsw assigned to this room during creating solution
 * and which nurse is assigned to this room on the given day and shift
*/

struct RoomInfo : public PatientRoomInfo
{
	RoomInfo() = default;

	RoomInfo(int maxCapacity, int currentCapacity) : 
		PatientRoomInfo(maxCapacity, currentCapacity)
	{}

	RoomInfo(const PatientRoomInfo& pri) :
		PatientRoomInfo(pri.maxCapacity, pri.maxCapacity)
	{
		genders = pri.genders;
		maxCapacity = pri.maxCapacity;
		currentCapacity = pri.currentCapacity;
		ageGroups = pri.ageGroups;
		unallowedPatients = pri.unallowedPatients;
		skillLevelsRequired = pri.skillLevelsRequired;
		shiftNameToProducedWorkload = pri.shiftNameToProducedWorkload;
		occupantIds = pri.occupantIds;
	}

	std::set<std::string> patientIds;
	std::map<std::string, std::string> nurseIdToShift;
	std::map<std::string, std::string> shiftToNurseId;
};