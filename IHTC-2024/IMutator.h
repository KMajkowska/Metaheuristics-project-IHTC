#pragma once

#include <random>

#include "CIndividual.h"
#include "ProblemData.h"

/**
 * @brief Class used as an interface to provide polymorphism to different ways of mutating our solution
*/
class IMutator
{
public:
	IMutator(std::mt19937& randGenerator, const ProblemData& problemData);
	virtual bool mutate(CIndividual& individual) const = 0;

	virtual std::string getMutatorName() const = 0;

protected:
	std::mt19937& randGenerator;
	const ProblemData& problemData;
};