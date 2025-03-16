#pragma once

#include "IHTCSolver.h"

/**
 * @brief Alternative for greedy solver to initializa SASOlver
*/
class RandomSolver : public IHTCSolver
{
public:
	RandomSolver(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const override;
};