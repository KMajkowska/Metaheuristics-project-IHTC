#pragma once

#include "PatientRoomInfo.h"

#include <set>

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