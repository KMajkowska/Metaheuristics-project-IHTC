#pragma once

#include "PatientDTO.h"

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" incoming patient is pretty similar, but we are separating json logic from algorithm logic
*/
class IncomingPatientDTO : public PatientDTO
{
public:
	IncomingPatientDTO() = default;
	IncomingPatientDTO(const IncomingPatientDTO& other) = default;

	bool isMandatory() const;
	int getSurgeryReleaseDay() const;
	int getSurgeryDueDay() const;
	int getSurgeryDuration() const;
	std::string getSurgeonId() const;
	std::vector<std::string> getIncompatibleRoomIds() const;

	void setMandatory(bool mandatory);
	void setSurgeryReleaseDay(int newSurgeryReleaseDay);
	void setSurgeruDueDay(int newSurgeryDueDay);
	void setSurgeryDuration(int newSurgeryDuration);
	void setSurgeonId(const std::string& newSurgeonId);
	void setIncompatibleRooms(std::vector<std::string> newIncompatibleRooms);

private:
	bool _mandatory;
	int _surgeryReleaseDay;
	int _surgeryDueDay;
	int _surgeryDuration;
	std::string _surgeonId;
	std::vector<std::string> _incompatibleRoomIds;
};

void to_json(nlohmann::json& j, const IncomingPatientDTO& incomingPatient);
void from_json(const nlohmann::json& j, IncomingPatientDTO& incomingPatient);
