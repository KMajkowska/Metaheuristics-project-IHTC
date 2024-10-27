#pragma once

#include <nlohmann/json.hpp>

#include "NurseOutputDTO.h"
#include "Patient.h"

class SolutionData
{
public:
	std::vector<NurseOutputDTO> getNurses() const;
	std::vector<Patient> getPatients() const;

	void setNurses(std::vector<NurseOutputDTO> newNurses);
	void setPatients(std::vector<Patient> newPatients);

private:
	std::vector<NurseOutputDTO> nurses;
	std::vector<Patient> patients;
};

void to_json(nlohmann::json& j, const SolutionData& data);
void from_json(const nlohmann::json& j, SolutionData& data);