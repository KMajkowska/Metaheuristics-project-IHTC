#pragma once

#include "IMutator.h"

class IHTCMutatorRoom : public IMutator
{
public:
	IHTCMutatorRoom(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomShuffleProbability);

	void mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:

	double roomShuffleProbability;
};