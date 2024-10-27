#pragma once

#include "IMutator.h"

class IHTCMutator : public IMutator
{
public:
	IHTCMutator(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability, double newRoomShuffleProbability);

	void mutate(CIndividual& individual) const;

private:
	int randomDay(int min, int max) const;

	double roomShuffleProbability;
	double dayShuffleProbability;
};