#include "IMutator.h"

IMutator::IMutator(std::mt19937& randGenerator, const ProblemData& problemData):
	randGenerator(randGenerator),
	problemData(problemData)
{}
