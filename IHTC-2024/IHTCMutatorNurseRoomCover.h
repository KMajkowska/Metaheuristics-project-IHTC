#pragma once

#include "IMutator.h"

class IHTCMutatorNurseRoomCover : public IMutator
{
public:
	IHTCMutatorNurseRoomCover(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomAddingToNurseProbability);

	void mutate(CIndividual& individual) const;

	std::string getMutatorName() const;


private:
	double roomAddingToNurseProbability;
};