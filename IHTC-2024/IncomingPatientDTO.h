#pragma once

#include "PatientDTO.h"

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
	bool mandatory;
	int surgery_release_day;
	int surgery_due_day;
	int surgery_duration;
	std::string surgeon_id;
	std::vector<std::string> incompatible_room_ids;
};

void to_json(nlohmann::json& j, const IncomingPatientDTO& incomingPatient);
void from_json(const nlohmann::json& j, IncomingPatientDTO& incomingPatient);
