#include "IncomingPatientDTO.h"

bool IncomingPatientDTO::isMandatory() const
{
    return mandatory;
}

int IncomingPatientDTO::getSurgeryReleaseDay() const
{
    return surgery_release_day;
}

int IncomingPatientDTO::getSurgeryDueDay() const
{
    return surgery_due_day;
}

int IncomingPatientDTO::getSurgeryDuration() const
{
    return surgery_duration;
}

std::string IncomingPatientDTO::getSurgeonId() const
{
    return surgeon_id;
}

std::vector<std::string> IncomingPatientDTO::getIncompatibleRoomIds() const
{
    return incompatible_room_ids;
}

void to_json(nlohmann::json& j, const IncomingPatientDTO& incomingPatient)
{
	nlohmann::to_json(j, static_cast<PatientDTO>(incomingPatient));

	j.update(
		{
			{"mandatory", incomingPatient.isMandatory()},
			{"surgery_release_day", incomingPatient.getSurgeryReleaseDay()},
			{"surgery_due_day", incomingPatient.getSurgeryDueDay()},
			{"surgery_duration", incomingPatient.getSurgeryDuration()},
			{"surgeon_id", incomingPatient.getSurgeonId()},
			{"incompatible_room_ids", incomingPatient.getIncompatibleRoomIds()}
		}
	);
}
