#pragma once

#include "PatientRoomInfo.h"

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
		skillLevelRequired = pri.skillLevelRequired;
		shiftNameToProducedWorkload = pri.shiftNameToProducedWorkload;
	}

	std::vector<std::string> patientIds;
	std::map<std::string, std::string> nurseIdToShift;
	std::map<std::string, std::string> shiftToNurseId;
};