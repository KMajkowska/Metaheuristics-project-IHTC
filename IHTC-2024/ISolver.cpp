#include "ISolver.h"

ISolver::ISolver(ProblemData& problemData, std::mt19937& randGenerator) :
	problemData(problemData),
	randGenerator(randGenerator)
{}
