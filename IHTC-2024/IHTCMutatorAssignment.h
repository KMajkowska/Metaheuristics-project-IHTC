#pragma once

#include "IMutator.h"

/**
 * @brief Mutator for changing assigned rooms for nurse. Randomly choose nurse, randomly choose room. If nurse has this room alreay, erase it. If not - add this room.
*/
class IHTCMutatorAssignment : public IMutator
{
public:
	IHTCMutatorAssignment(std::mt19937& randGenerator, const ProblemData& problemData, double swapAssignmentsProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;
};