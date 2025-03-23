#include "GreedySolverBuilder.h"

GreedySolverBuilder::GreedySolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
    IHTCSolverBuilder(problemData, randGenerator, consumer)
{}

std::optional<std::shared_ptr<IHTCSolver>> GreedySolverBuilder::prepareForBuild() const
{
    return std::make_shared<GreedySolver>(_problemData, _randGenerator, _consumer);
}
