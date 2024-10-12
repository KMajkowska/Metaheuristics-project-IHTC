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

std::vector<std::string> IncomingPatientDTO::getIncompatibleRoomIds()
{
    return incompatible_room_ids;
}
