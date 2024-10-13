#pragma once

#include "IProblem.h"

#include <random>

class RandomProblem : public IProblem
{
public:
	RandomProblem(std::mt19937& randGenerator);

	double eval(const CIndividual& individual) const;

private:
	std::mt19937& randGenerator;
};