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

void PatientDTO::setId(std::string newId)
{
    id = newId;
}

void PatientDTO::setGender(std::string newGender)
{
    gender = newGender;
}

void PatientDTO::setAgeGroup(std::string newAgeGroup)
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