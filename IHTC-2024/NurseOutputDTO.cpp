#include "NurseOutputDTO.h"

NurseOutputDTO::NurseOutputDTO(std::string newId, std::vector<Assignment> newAssignments) :
    _id(newId), 
    _assignments(newAssignments)
{}

std::string NurseOutputDTO::id() const
{
    return _id;
}

std::vector<Assignment> NurseOutputDTO::assignments() const
{
    return _assignments;
}

void NurseOutputDTO::setId(const std::string& newId)
{
    _id = newId;
}

void NurseOutputDTO::setAssignments(std::vector<Assignment> newAssignments)
{
    _assignments = newAssignments;
}

void to_json(nlohmann::json& j, const NurseOutputDTO& data)
{
    j = nlohmann::json
    {
        {"id", data.id()},
        {"assignments", data.assignments()},
    };
}

void from_json(const nlohmann::json& j, NurseOutputDTO& data)
{
    data.setId(j.at("id").get<std::string>());
    data.setAssignments(j.at("assignments").get<std::vector<Assignment>>());
}
