#include "RandomSolver.h"

RandomSolver::RandomSolver(std::mt19937& randGenerator) : 
    randGenerator(randGenerator)
{
}

std::vector<CIndividual> RandomSolver::solve(const ProblemData& problemData, const Problem& problem) const
{
    return std::vector<CIndividual>();
}
