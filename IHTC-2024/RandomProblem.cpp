#include "RandomProblem.h"

RandomProblem::RandomProblem(std::mt19937& randGenerator) :
	randGenerator(randGenerator)
{}

double RandomProblem::eval(const CIndividual& individual) const
{
	std::uniform_real_distribution<double> distrib(0.0, DBL_MAX);

	return distrib(randGenerator);
}
