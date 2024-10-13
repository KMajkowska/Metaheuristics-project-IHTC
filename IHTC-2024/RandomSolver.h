#pragma once

#include "ISolver.h"

class RandomSolver : public ISolver
{
public:
	RandomSolver(std::mt19937& randGenerator);

	CIndividual solve(const ProblemData& problemData, const IProblem& problem) const;

private:
	std::mt19937& randGenerator;
};