#include "RoomInfo.h"

RoomInfo::RoomInfo(int maxCapacity, int currentCapacity) :
	PatientRoomInfo(maxCapacity, currentCapacity) 
{}

RoomInfo::RoomInfo(const PatientRoomInfo& pri) :
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

void RoomInfo::setPatientIds(std::set<std::string>&& patientIds)
{
	_patientIds = std::move(patientIds);
}

void RoomInfo::setNurseidToShift(std::map<std::string, std::string>&& nurseIdToShift)
{
	_nurseIdToShift = std::move(nurseIdToShift);
}

void RoomInfo::setShiftToNurseId(std::map<std::string, std::string>&& shiftToNurseId)
{
	_shiftToNurseId = std::move(shiftToNurseId);
}

std::set<std::string>& RoomInfo::patientIds()
{
	return _patientIds;
}

std::map<std::string, std::string>& RoomInfo::nurseIdToShift()
{
	return _nurseIdToShift;
}

std::map<std::string, std::string>& RoomInfo::shiftToNurseId()
{
	return _shiftToNurseId;
}
