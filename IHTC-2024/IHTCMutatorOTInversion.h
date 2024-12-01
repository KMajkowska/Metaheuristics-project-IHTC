#pragma once

#include "IHTCMutatorOperatingTheaters.h"
#include "other.h"

class IHTCMutatorOTInversion : public IHTCMutatorOperatingTheaters
{
public:
	IHTCMutatorOTInversion(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:
	double mutationProbability;
};