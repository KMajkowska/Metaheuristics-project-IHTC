#pragma once

#include "IMutator.h"

class IHTCMutatorAssignmentsSwap : public IMutator
{
public:
	IHTCMutatorAssignmentsSwap(std::mt19937& randGenerator, const ProblemData& problemData, double swapAssignmentsProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:
	double swapAssignmentsProbability;
};