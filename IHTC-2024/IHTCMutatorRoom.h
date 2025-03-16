#pragma once

#include "IMutator.h"

class IHTCMutatorRoom : public IMutator
{
public:
	IHTCMutatorRoom(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomShuffleProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;
};