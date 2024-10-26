#pragma once
#include <vector>
#include <random>

#include "IProblem.h"
#include "ProblemData.h"
#include "CIndividual.h"

class ISolver
{
public:
	ISolver(ProblemData& problemData, std::mt19937& randGenerator);
	virtual CIndividual solve(const IProblem& problem) const = 0;

protected:
	ProblemData& problemData;

	std::mt19937& randGenerator;
};