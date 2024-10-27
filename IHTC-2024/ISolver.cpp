#include "ISolver.h"

ISolver::ISolver(const ProblemData& problemData, std::mt19937& randGenerator) :
	problemData(problemData),
	randGenerator(randGenerator)
{}
