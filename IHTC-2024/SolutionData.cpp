#include "SolutionData.h"

std::vector<NurseOutputDTO> SolutionData::getNurses() const
{
    return nurses;
}

std::vector<Patient> SolutionData::getPatients() const
{
    return patients;
}

void SolutionData::setNurses(std::vector<NurseOutputDTO> newNurses)
{
    nurses = newNurses;
}

void SolutionData::setPatients(std::vector<Patient> newPatients)
{
    patients = newPatients;
}

void to_json(nlohmann::json& j, const SolutionData& data)
{
    j = nlohmann::json
    {
        {"nurses", data.getNurses()},
        {"patients", data.getPatients()},
    };
}

void from_json(const nlohmann::json& j, SolutionData& data)
{
    data.setNurses(j.at("nurses").get<std::vector<NurseOutputDTO>>());
    data.setPatients(j.at("patients").get<std::vector<Patient>>());
}
