#pragma once

#include "IHTCMutatorOperatingTheaters.h"
#include "other.h"

/**
 * @brief Mutator for changinf OT for patient. Randomly choose patient and OT and assign this OT to the patient. No matter if this OT has time and is open this day.
*/
class IHTCMutatorOT : public IHTCMutatorOperatingTheaters
{
public:
	IHTCMutatorOT(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;
};