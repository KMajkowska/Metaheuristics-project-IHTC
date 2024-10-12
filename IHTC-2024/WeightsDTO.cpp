#include "WeightsDTO.h"

int WeightsDTO::getRoomMixedAge() const
{
    return room_mixed_age;
}

int WeightsDTO::getRoomNurseSkill() const
{
    return room_nurse_skill;
}

int WeightsDTO::getContinuityOfCare() const
{
    return continuity_of_care;
}

int WeightsDTO::getNurseEccesiveWorkload() const
{
    return nurse_eccesive_workload;
}

int WeightsDTO::getOpenOperatingTheater() const
{
    return open_operating_theater;
}

int WeightsDTO::getSurgeonTransfer() const
{
    return surgeon_transfer;
}

int WeightsDTO::getPatientDelay() const
{
    return patient_delay;
}

int WeightsDTO::getUnscheduledOptional() const
{
    return unscheduled_optional;
}

void WeightsDTO::setRoomMixedAge(int newRoomMixedAge)
{
    room_mixed_age = newRoomMixedAge;
}

void WeightsDTO::setRoomNurseSkill(int newRoomNurseSkill)
{
    room_nurse_skill = newRoomNurseSkill;
}

void WeightsDTO::setContinuityOfCare(int newContinuityOfCare)
{
    continuity_of_care = newContinuityOfCare;
}

void WeightsDTO::setNurseEccesiveWorkload(int newNurseEccesiveWorkload)
{
    nurse_eccesive_workload = newNurseEccesiveWorkload;
}

void WeightsDTO::setOpenOperatingTheater(int newOpenOperatingTheater)
{
    open_operating_theater = newOpenOperatingTheater;
}

void WeightsDTO::setSurgeonTransfer(int newSurgeonTransfer)
{
    surgeon_transfer = newSurgeonTransfer;
}

void WeightsDTO::setPatientDelay(int newPatientDelay)
{
    patient_delay = newPatientDelay;
}

void WeightsDTO::setUnscheduledOptional(int newUnscheduledOptional)
{
    unscheduled_optional = newUnscheduledOptional;
}

void to_json(nlohmann::json& j, const WeightsDTO& weights)
{
    j = nlohmann::json
    {
        {"room_mixed_age", weights.getRoomMixedAge()},
        {"room_nurse_skil", weights.getRoomNurseSkill()},
        {"continuity_of_care", weights.getContinuityOfCare()},
        {"nurse_eccesive_workload", weights.getNurseEccesiveWorkload()},
        {"open_operating_theater", weights.getOpenOperatingTheater()},
        {"surgeon_transfer", weights.getSurgeonTransfer()},
        {"patient_delay", weights.getPatientDelay()},
        {"unscheduled_optional", weights.getUnscheduledOptional()},

    };
}