#pragma once
#include <vector>
#include <random>

#include "IProblem.h"
#include "ProblemData.h"
#include "CIndividual.h"

class ISolver
{
public:
	ISolver(const ProblemData& problemData, std::mt19937& randGenerator);
	virtual ~ISolver() = default;

	virtual CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const = 0;

protected:
	const ProblemData& problemData;
	std::mt19937& randGenerator;
};