#pragma once

#include "IMutator.h"

class IHTCMutatorNurseRoomCover : public IMutator
{
public:
	IHTCMutatorNurseRoomCover(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomAddingToNurseProbability);

	void mutate(CIndividual& individual) const;

private:
	double roomAddingToNurseProbability;
};