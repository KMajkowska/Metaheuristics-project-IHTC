#include "RandomSolverBuilder.h"

RandomSolverBuilder::RandomSolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
    IHTCSolverBuilder(problemData, randGenerator, consumer)
{}

std::optional<std::shared_ptr<IHTCSolver>> RandomSolverBuilder::prepareForBuild() const
{
    return std::make_shared<RandomSolver>(_problemData, _randGenerator, _consumer);
}
