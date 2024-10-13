#pragma once

#include <nlohmann/json.hpp>

#include "NurseOutputDTO.h"
#include "PatientOutputDTO.h"

class SolutionData
{
public:
	std::vector<NurseOutputDTO> getNurses() const;
	std::vector<PatientOutputDTO> getPatients() const;

	void setNurses(std::vector<NurseOutputDTO> newNurses);
	void setPatients(std::vector<PatientOutputDTO> newPatients);

private:
	std::vector<NurseOutputDTO> nurses;
	std::vector<PatientOutputDTO> patients;
};

void to_json(nlohmann::json& j, const SolutionData& data);
void from_json(const nlohmann::json& j, SolutionData& data);