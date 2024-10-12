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

void IncomingPatientDTO::setMandatory(bool mandatory)
{
    this->mandatory = mandatory;
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

void from_json(const nlohmann::json& j, IncomingPatientDTO& incomingPatient)
{
    nlohmann::from_json(j, static_cast<PatientDTO&>(incomingPatient));

    incomingPatient.setMandatory(j.at("mandatory").get<bool>());
    incomingPatient.setSurgeryReleaseDay(j.at("surgery_release_day").get<int>());
    incomingPatient.setSurgeruDueDay(j.at("surgery_due_day").get<int>());
    incomingPatient.setSurgeryDuration(j.at("surgery_duration").get<int>());
    incomingPatient.setSurgeonId(j.at("surgeon_id").get<std::string>());
    incomingPatient.setIncompatibleRooms(j.at("incompatible_room_ids").get<std::vector<std::string>>());
}
