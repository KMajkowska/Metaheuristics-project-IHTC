#include "WeightsDTO.h"

int WeightsDTO::getRoomMixedAge() const
{
    return room_mixed_age;
}

int WeightsDTO::getRoomNurseSkil() const
{
    return room_nurse_skil;
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

void to_json(nlohmann::json& j, const WeightsDTO& weights)
{
	j = nlohmann::json
	{
		{"room_mixed_age", weights.getRoomMixedAge()},
		{"room_nurse_skil", weights.getRoomNurseSkil()},
		{"continuity_of_care", weights.getContinuityOfCare()},
		{"nurse_eccesive_workload", weights.getNurseEccesiveWorkload()},
		{"open_operating_theater", weights.getOpenOperatingTheater()},
		{"surgeon_transfer", weights.getSurgeonTransfer()},
		{"patient_delay", weights.getPatientDelay()},
		{"unscheduled_optional", weights.getUnscheduledOptional()},

	};
}
