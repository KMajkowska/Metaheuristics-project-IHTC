#include "RoomInfo.h"

RoomInfo::RoomInfo(int maxCapacity, int currentCapacity) :
	PatientRoomInfo(maxCapacity, currentCapacity) 
{}

RoomInfo::RoomInfo(const PatientRoomInfo& pri) :
	PatientRoomInfo(pri._maxCapacity, pri._maxCapacity)
{
	_genders = pri._genders;
	_maxCapacity = pri._maxCapacity;
	_currentCapacity = pri._currentCapacity;
	_ageGroups = pri._ageGroups;
	_unallowedPatients = pri._unallowedPatients;
	_skillLevelsRequired = pri._skillLevelsRequired;
	_shiftNameToProducedWorkload = pri._shiftNameToProducedWorkload;
	_occupantIds = pri._occupantIds;
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
