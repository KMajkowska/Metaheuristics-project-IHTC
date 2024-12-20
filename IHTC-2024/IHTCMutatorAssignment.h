#pragma once

#include "IMutator.h"

class IHTCMutatorAssignment : public IMutator
{
public:
	IHTCMutatorAssignment(std::mt19937& randGenerator, const ProblemData& problemData, double swapAssignmentsProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:
	double swapAssignmentsProbability;
};