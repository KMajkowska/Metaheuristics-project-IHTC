#pragma once
#include <vector>
#include <random>

#include "Problem.h"
#include "ProblemData.h"
#include "CIndividual.h"

class ISolver
{
public:
	virtual std::vector<CIndividual> solve(const ProblemData& problemData, const Problem& problem) const = 0;
};