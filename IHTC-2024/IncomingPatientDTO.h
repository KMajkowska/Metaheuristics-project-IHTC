#pragma once
#include "PatientDTO.h"

class IncomingPatientDTO : public PatientDTO
{
private:
	bool mandatory;
	int surgery_release_day;
	int surgery_due_day;
	int surgery_duration;
	std::string surgeon_id;
	std::vector<std::string> incompatible_room_ids;
};