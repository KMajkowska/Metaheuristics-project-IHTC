#pragma once

#include <nlohmann/json.hpp>

#include "NurseOutputDTO.h"
#include "Patient.h"
#include "ProblemData.h"

/**
 * @brief Data which are written to the solution file. Solution is combined with nurses and their assigned rooms and patients with rooms, OT and day.
 * Individual is required as a solution
*/
class SolutionData
{
public:
	SolutionData() = default;
	SolutionData(const ProblemData& problemData, const CIndividual& individual);

	void setNurses(std::vector<NurseOutputDTO> newNurses);
	void setPatients(std::vector<Patient> newPatients);
	void setFitness(double fitness);

	std::vector<NurseOutputDTO> nurses() const;
	std::vector<Patient> patients() const;
	double fitness() const;

private:
	std::vector<NurseOutputDTO> _nurses;
	std::vector<Patient> _patients;

	double _fitness { std::numeric_limits<double>::max() };
};

void to_json(nlohmann::json& j, const SolutionData& data);
void from_json(const nlohmann::json& j, SolutionData& data);