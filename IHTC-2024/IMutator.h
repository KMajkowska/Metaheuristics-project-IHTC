#pragma once

#include <random>

#include "CIndividual.h"
#include "ProblemData.h"

class IMutator
{
public:
	IMutator(std::mt19937& randGenerator, const ProblemData& problemData);
	virtual void mutate(CIndividual& individual) const = 0;

	virtual std::string getMutatorName() const = 0;

protected:
	std::mt19937& randGenerator;
	const ProblemData& problemData;
};