#include "WeightsDTO.h"

int WeightsDTO::getRoomMixedAge() const
{
    return _roomMixedAge;
}

int WeightsDTO::getRoomNurseSkill() const
{
    return _roomNurseSkill;
}

int WeightsDTO::getContinuityOfCare() const
{
    return _continuityOfCare;
}

int WeightsDTO::getNurseEccessiveWorkload() const
{
    return _nurseEccessiveWorkload;
}

int WeightsDTO::getOpenOperatingTheater() const
{
    return _openOperatingTheater;
}

int WeightsDTO::getSurgeonTransfer() const
{
    return _surgeonTransfer;
}

int WeightsDTO::getPatientDelay() const
{
    return _patientDelay;
}

int WeightsDTO::getUnscheduledOptional() const
{
    return _unscheduledOptional;
}

void WeightsDTO::setRoomMixedAge(int newRoomMixedAge)
{
    _roomMixedAge = newRoomMixedAge;
}

void WeightsDTO::setRoomNurseSkill(int newRoomNurseSkill)
{
    _roomNurseSkill = newRoomNurseSkill;
}

void WeightsDTO::setContinuityOfCare(int newContinuityOfCare)
{
    _continuityOfCare = newContinuityOfCare;
}

void WeightsDTO::setNurseEccessiveWorkload(int newNurseEccessiveWorkload)
{
    _nurseEccessiveWorkload = newNurseEccessiveWorkload;
}

void WeightsDTO::setOpenOperatingTheater(int newOpenOperatingTheater)
{
    _openOperatingTheater = newOpenOperatingTheater;
}

void WeightsDTO::setSurgeonTransfer(int newSurgeonTransfer)
{
    _surgeonTransfer = newSurgeonTransfer;
}

void WeightsDTO::setPatientDelay(int newPatientDelay)
{
    _patientDelay = newPatientDelay;
}

void WeightsDTO::setUnscheduledOptional(int newUnscheduledOptional)
{
    _unscheduledOptional = newUnscheduledOptional;
}

int WeightsDTO::getMaxWeight() const
{
    return std::max(
        {
            _roomMixedAge,
            _roomNurseSkill,
            _continuityOfCare,
            _nurseEccessiveWorkload,
            _openOperatingTheater,
            _surgeonTransfer,
            _patientDelay,
            _unscheduledOptional
        }
    );
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