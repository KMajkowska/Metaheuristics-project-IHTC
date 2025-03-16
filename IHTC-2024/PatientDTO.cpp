#include "PatientDTO.h"

std::string PatientDTO::id() const
{
    return _id;
}

std::string PatientDTO::gender() const
{
    return _gender;
}

std::string PatientDTO::ageGroup() const
{
    return _ageGroup;
}

int PatientDTO::lengthOfStay() const
{
    return _lengthOfStay;
}

std::vector<int> PatientDTO::workloadProduced() const
{
    return _workloadProduced;
}

std::vector<int> PatientDTO::skillLevelRequired() const
{
    return _skillLevelRequired;
}

void PatientDTO::setId(const std::string& newId)
{
    _id = newId;
}

void PatientDTO::setGender(const std::string& newGender)
{
    _gender = newGender;
}

void PatientDTO::setAgeGroup(const std::string& newAgeGroup)
{
    _ageGroup = newAgeGroup;
}

void PatientDTO::setLengthOfStay(int newLengthOfStay)
{
    _lengthOfStay = newLengthOfStay;
}

void PatientDTO::setWorkloadProduced(std::vector<int> newWorkloadProduced)
{
    _workloadProduced = newWorkloadProduced;
}

void PatientDTO::setSkillLevelRequired(std::vector<int> newSkillLevelRequired)
{
    _skillLevelRequired = newSkillLevelRequired;
}

void to_json(nlohmann::json& j, const PatientDTO& patient)
{
    j = nlohmann::json
    {
        {"id", patient.id()},
        {"gender", patient.gender()},
        {"age_group", patient.ageGroup()},
        {"length_of_stay", patient.lengthOfStay()},
        {"workload_produced", patient.workloadProduced()},
        {"skill_level_required", patient.skillLevelRequired()}
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
