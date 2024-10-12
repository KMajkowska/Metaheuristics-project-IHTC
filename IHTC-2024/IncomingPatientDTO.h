#pragma once

#include "PatientDTO.h"

class IncomingPatientDTO : public PatientDTO
{
public:
	bool isMandatory() const;
	int getSurgeryReleaseDay() const;
	int getSurgeryDueDay() const;
	int getSurgeryDuration() const;
	std::string getSurgeonId() const;
	std::vector<std::string> getIncompatibleRoomIds();


private:
	bool mandatory;
	int surgery_release_day;
	int surgery_due_day;
	int surgery_duration;
	std::string surgeon_id;
	std::vector<std::string> incompatible_room_ids;
};