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

std::vector<int> PatientDTO::getWorkloadProduced()
{
    return workload_produced;
}

std::vector<int> PatientDTO::getSkillLevelRequired()
{
    return skill_level_required;
}
