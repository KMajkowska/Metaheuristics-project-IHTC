#pragma once

#include "IMutator.h"

class IHTCMutatorDay : public IMutator
{
public:
	IHTCMutatorDay(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability);

	void mutate(CIndividual& individual) const;

private:
	int randomDay(int min, int max) const;

	double dayShuffleProbability;
};