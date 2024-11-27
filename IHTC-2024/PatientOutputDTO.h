#pragma once

#include "Patient.h"

class PatientOutputDTO : public Patient
{
public:
	PatientOutputDTO() = default;
	PatientOutputDTO(const std::string& id, int admissionDay, const std::string& roomId, const std::string& operationTheater);

	std::string getId() const;

	void setId(const std::string& newId);

private:
	std::string id;
};

void to_json(nlohmann::json& j, const PatientOutputDTO& data);
void from_json(const nlohmann::json& j, PatientOutputDTO& data);