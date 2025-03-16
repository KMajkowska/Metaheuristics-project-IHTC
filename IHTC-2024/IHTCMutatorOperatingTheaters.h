#pragma once

#include <vector>

#include "IMutator.h"

/**
 * @brief Mutator to change Operating Theaters for patient. We choose random OTs and Patients and we change their assined patients/OTs
*/
class IHTCMutatorOperatingTheaters : public IMutator
{
public:
	IHTCMutatorOperatingTheaters(std::mt19937& randGenerator, const ProblemData& problemData, double mutationProbability);

protected:
	std::vector<std::unordered_map<std::string, std::vector<std::string>>> getOperatingTheaterHelper(CIndividual& individual) const;
};