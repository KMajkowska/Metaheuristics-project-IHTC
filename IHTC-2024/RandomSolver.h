#pragma once

#include "ISolver.h"

class RandomSolver : public ISolver
{
public:
	RandomSolver(std::mt19937& randGenerator);

	std::vector<CIndividual> solve(const ProblemData& problemData, const Problem& problem) const;

private:
	std::mt19937& randGenerator;
};