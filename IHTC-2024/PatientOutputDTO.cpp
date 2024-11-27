#include "PatientOutputDTO.h"

PatientOutputDTO::PatientOutputDTO(const std::string& id, int admissionDay, const std::string& roomId, const std::string& operationTheater) :
    Patient(admissionDay, roomId, operationTheater),
    id(id)
{}

std::string PatientOutputDTO::getId() const
{
    return id;
}

void PatientOutputDTO::setId(const std::string& newId)
{
    id = newId;
}

void to_json(nlohmann::json& j, const PatientOutputDTO& data)
{
    nlohmann::to_json(j, static_cast<Patient>(data));

    j.update({ {"id", data.getId()} });
}

void from_json(const nlohmann::json& j, PatientOutputDTO& data)
{
    nlohmann::from_json(j, static_cast<Patient&>(data));

    data.setId(j.at("id").get<std::string>());
}
