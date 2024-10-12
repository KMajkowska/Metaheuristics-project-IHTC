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

void IncomingPatientDTO::changeMandatorinnes()
{
    mandatory = !mandatory;
}

void IncomingPatientDTO::setSurgeryReleaseDay(int newSurgeryReleaseDay)
{
    surgery_release_day = newSurgeryReleaseDay;
}

void IncomingPatientDTO::setSurgeruDueDay(int newSurgeryDueDay) 
{
    surgery_due_day = newSurgeryDueDay;
}

void IncomingPatientDTO::setSurgeryDuration(int newSurgeryDuration)
{
    surgery_duration = newSurgeryDuration;
}

void IncomingPatientDTO::setSurgeonId(std::string newSurgeonId)
{
    surgeon_id = newSurgeonId;
}

void IncomingPatientDTO::setIncompatibleRooms(std::vector<std::string> newIncompatibleRooms)
{
    incompatible_room_ids = newIncompatibleRooms;
}