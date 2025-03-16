#pragma once

#include "PatientRoomInfo.h"

#include <set>

/**
 * @brief Extension of PatientRoomInfo, where we also store id of nurse in given day and shift, list of patientsw assigned to this room during creating solution
 * and which nurse is assigned to this room on the given day and shift
*/
class RoomInfo : public PatientRoomInfo
{
public:
	RoomInfo() = default;
	RoomInfo(int maxCapacity, int currentCapacity);
	RoomInfo(const PatientRoomInfo& pri);

	void setPatientIds(std::set<std::string>&& patientIds);
	void setNurseidToShift(std::map<std::string, std::string>&& nurseIdToShift);
	void setShiftToNurseId(std::map<std::string, std::string>&& shiftToNurseId);

	std::set<std::string>& patientIds();
	std::map<std::string, std::string>& nurseIdToShift();
	std::map<std::string, std::string>& shiftToNurseId();

private:
	std::set<std::string> _patientIds;
	std::map<std::string, std::string> _nurseIdToShift;
	std::map<std::string, std::string> _shiftToNurseId;
};