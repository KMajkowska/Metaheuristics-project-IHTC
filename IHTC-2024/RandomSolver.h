#pragma once

#include "IHTCSolver.h"

class RandomSolver : public IHTCSolver
{
public:
	RandomSolver(const ProblemData& problemData, std::mt19937& randGenerator, Logger& logger);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;
};