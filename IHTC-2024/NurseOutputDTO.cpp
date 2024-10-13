#include "NurseOutputDTO.h"

NurseOutputDTO::NurseOutputDTO(std::string newId, std::vector<Assignment> newAssignments) :id(newId), assignments(newAssignments)
{
}

std::string NurseOutputDTO::getId() const
{
    return id;
}

std::vector<Assignment> NurseOutputDTO::getAssignments() const
{
    return assignments;
}

void NurseOutputDTO::setId(const std::string& newId)
{
    id = newId;
}

void NurseOutputDTO::setAssignments(std::vector<Assignment> newAssignments)
{
    assignments = newAssignments;
}

void to_json(nlohmann::json& j, const NurseOutputDTO& data)
{
    j = nlohmann::json
    {
        {"id", data.getId()},
        {"assignments", data.getAssignments()},
    };
}

void from_json(const nlohmann::json& j, NurseOutputDTO& data)
{
    data.setId(j.at("id").get<std::string>());
    data.setAssignments(j.at("assignments").get<std::vector<Assignment>>());
}
