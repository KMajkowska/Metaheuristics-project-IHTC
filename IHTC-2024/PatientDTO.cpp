#include "PatientDTO.h"

std::string PatientDTO::getId() const
{
    return id;
}

std::string PatientDTO::getGender() const
{
    return gender;
}

std::string PatientDTO::getAgeGroup() const
{
    return age_group;
}

int PatientDTO::getLengthOfStay() const
{
    return length_of_stay;
}

std::vector<int> PatientDTO::getWorkloadProduced() const
{
    return workload_produced;
}

std::vector<int> PatientDTO::getSkillLevelRequired() const
{
    return skill_level_required;
}

void PatientDTO::setId(const std::string& newId)
{
    id = newId;
}

void PatientDTO::setGender(const std::string& newGender)
{
    gender = newGender;
}

void PatientDTO::setAgeGroup(const std::string& newAgeGroup)
{
    age_group = newAgeGroup;
}

void PatientDTO::setLengthOfStay(int newLengthOfStay)
{
    length_of_stay = newLengthOfStay;
}

void PatientDTO::setWorkloadProduced(std::vector<int> newWorkloadProduced)
{
    workload_produced = newWorkloadProduced;
}

void PatientDTO::setSkillLevelRequired(std::vector<int> newSkillLevelRequired)
{
    skill_level_required = newSkillLevelRequired;
}

void to_json(nlohmann::json& j, const PatientDTO& patient)
{
    j = nlohmann::json
    {
        {"id", patient.getId()},
        {"gender", patient.getGender()},
        {"age_group", patient.getAgeGroup()},
        {"length_of_stay", patient.getLengthOfStay()},
        {"workload_produced", patient.getWorkloadProduced()},
        {"skill_level_required", patient.getSkillLevelRequired()}
    };
}

void from_json(const nlohmann::json& j, PatientDTO& patient)
{
    patient.setId(j.at("id").get<std::string>());
    patient.setGender(j.at("gender").get<std::string>());
    patient.setAgeGroup(j.at("age_group").get<std::string>());
    patient.setLengthOfStay(j.at("length_of_stay").get<int>());
    patient.setWorkloadProduced(j.at("workload_produced").get<std::vector<int>>());
    patient.setSkillLevelRequired(j.at("skill_level_required").get<std::vector<int>>());
}
