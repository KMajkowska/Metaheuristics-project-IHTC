#include "ISolver.h"

ISolver::ISolver(const ProblemData& problemData, std::mt19937& randGenerator) :
	_problemData(problemData),
	_randGenerator(randGenerator)
{}
