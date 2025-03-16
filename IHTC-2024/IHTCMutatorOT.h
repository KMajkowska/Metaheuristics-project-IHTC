#pragma once

#include "IHTCMutatorOperatingTheaters.h"
#include "other.h"

class IHTCMutatorOT : public IHTCMutatorOperatingTheaters
{
public:
	IHTCMutatorOT(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;

private:
	double _mutationProbability;
};