#pragma once

#include "IMutator.h"

/**
 * @brief Specialized mutator runned every given number of iterations. It added uncovereed rooms for nurse, which is on given shift and given day. 
 * it helps with the problem of uncovered rooms which are never covered. 
 * It also happend with given probability. However it is not regular used mutator, but specialized one runner only when are uncovered roomes or by given number of iterations
*/
class IHTCMutatorNurseRoomCover : public IMutator
{
public:
	IHTCMutatorNurseRoomCover(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomAddingToNurseProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;


private:
	double roomAddingToNurseProbability;
};