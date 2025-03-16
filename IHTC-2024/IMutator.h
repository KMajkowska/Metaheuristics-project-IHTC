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
	IMutator(std::mt19937& randGenerator, const ProblemData& problemData, double mutationProbability);
	virtual ~IMutator() = default;

	virtual bool mutate(CIndividual& individual) const = 0;

	virtual std::string mutatorName() const = 0;

protected:
	std::mt19937& _randGenerator;
	const ProblemData& _problemData;

	double _mutationProbability{ 0 };
};