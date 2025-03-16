#pragma once

#include "IMutator.h"

/**
 * @brief Mutator where we choose random patient and we assign these patient random room, different than current room
*/
class IHTCMutatorRoom : public IMutator
{
public:
	IHTCMutatorRoom(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomShuffleProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;
};