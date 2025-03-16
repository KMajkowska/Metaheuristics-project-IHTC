#include "RandomSolverBuilder.h"

RandomSolverBuilder::RandomSolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
    IHTCSolverBuilder(params, problemData, randGenerator, consumer)
{}

std::optional<RandomSolver> RandomSolverBuilder::prepareForBuild() const
{
    return RandomSolver(_problemData, _randGenerator, _consumer);
}
