#include "IncomingPatientDTO.h"

bool IncomingPatientDTO::isMandatory() const
{
    return _mandatory;
}

int IncomingPatientDTO::getSurgeryReleaseDay() const
{
    return _surgeryReleaseDay;
}

int IncomingPatientDTO::getSurgeryDueDay() const
{
    return _surgeryDueDay;
}

int IncomingPatientDTO::getSurgeryDuration() const
{
    return _surgeryDuration;
}

std::string IncomingPatientDTO::getSurgeonId() const
{
    return _surgeonId;
}

std::vector<std::string> IncomingPatientDTO::getIncompatibleRoomIds() const
{
    return _incompatibleRoomIds;
}

void IncomingPatientDTO::setMandatory(bool mandatory)
{
    this->_mandatory = mandatory;
}

void IncomingPatientDTO::setSurgeryReleaseDay(int newSurgeryReleaseDay)
{
    _surgeryReleaseDay = newSurgeryReleaseDay;
}

void IncomingPatientDTO::setSurgeruDueDay(int newSurgeryDueDay) 
{
    _surgeryDueDay = newSurgeryDueDay;
}

void IncomingPatientDTO::setSurgeryDuration(int newSurgeryDuration)
{
    _surgeryDuration = newSurgeryDuration;
}

void IncomingPatientDTO::setSurgeonId(const std::string& newSurgeonId)
{
    _surgeonId = newSurgeonId;
}

void IncomingPatientDTO::setIncompatibleRooms(std::vector<std::string> newIncompatibleRooms)
{
    _incompatibleRoomIds = newIncompatibleRooms;
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
    incomingPatient.setSurgeryDuration(j.at("surgery_duration").get<int>());
    incomingPatient.setSurgeonId(j.at("surgeon_id").get<std::string>());
    incomingPatient.setIncompatibleRooms(j.at("incompatible_room_ids").get<std::vector<std::string>>());

    if (j.contains("surgery_due_day")) {
        incomingPatient.setSurgeruDueDay(j.at("surgery_due_day").get<int>());
    }
    else {
        incomingPatient.setSurgeruDueDay(INT_MAX);
    }
}
