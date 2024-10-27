#pragma once

#include "ISolver.h"

class RandomSolver : public ISolver
{
public:
	RandomSolver(const ProblemData& problemData, std::mt19937& randGenerator);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;
};