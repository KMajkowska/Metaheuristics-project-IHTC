#pragma once

#include "IHTCMutatorOperatingTheaters.h"
#include "other.h"

class IHTCMutatorOTInversion : public IHTCMutatorOperatingTheaters
{
public:
	IHTCMutatorOTInversion(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability);

	void mutate(CIndividual& individual) const;

private:
	double mutationProbability;
};