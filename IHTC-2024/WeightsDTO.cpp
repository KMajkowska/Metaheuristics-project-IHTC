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

int WeightsDTO::getNurseEccessiveWorkload() const
{
    return nurse_eccessive_workload;
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

void WeightsDTO::setNurseEccessiveWorkload(int newNurseEccessiveWorkload)
{
    nurse_eccessive_workload = newNurseEccessiveWorkload;
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
        {"room_nurse_skill", weights.getRoomNurseSkill()},
        {"continuity_of_care", weights.getContinuityOfCare()},
        {"nurse_eccessive_workload", weights.getNurseEccessiveWorkload()},
        {"open_operating_theater", weights.getOpenOperatingTheater()},
        {"surgeon_transfer", weights.getSurgeonTransfer()},
        {"patient_delay", weights.getPatientDelay()},
        {"unscheduled_optional", weights.getUnscheduledOptional()},

    };
}

void from_json(const nlohmann::json& j, WeightsDTO& weights)
{
    weights.setRoomMixedAge(j.at("room_mixed_age").get<int>());
    weights.setRoomNurseSkill(j.at("room_nurse_skill").get<int>());
    weights.setContinuityOfCare(j.at("continuity_of_care").get<int>());
    weights.setNurseEccessiveWorkload(j.at("nurse_eccessive_workload").get<int>());
    weights.setOpenOperatingTheater(j.at("open_operating_theater").get<int>());
    weights.setSurgeonTransfer(j.at("surgeon_transfer").get<int>());
    weights.setPatientDelay(j.at("patient_delay").get<int>());
    weights.setUnscheduledOptional(j.at("unscheduled_optional").get<int>());
}