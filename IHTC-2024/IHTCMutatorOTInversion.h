#pragma once

#include "IHTCMutatorOperatingTheaters.h"
#include "other.h"

/**
 * @brief Mutator where we randomly choose two OTs on random day and we assign patients from OT1 to OT2 and from OT2 to OT1
 */
class IHTCMutatorOTInversion : public IHTCMutatorOperatingTheaters
{
public:
	IHTCMutatorOTInversion(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:
	double mutationProbability;
};