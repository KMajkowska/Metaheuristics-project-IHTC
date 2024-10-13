#pragma once
#include <vector>
#include <random>

#include "IProblem.h"
#include "ProblemData.h"
#include "CIndividual.h"

class ISolver
{
public:
	virtual CIndividual solve(const ProblemData& problemData, const IProblem& problem) const = 0;
};