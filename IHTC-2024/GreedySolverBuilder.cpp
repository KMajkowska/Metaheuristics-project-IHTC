#include "GreedySolverBuilder.h"

GreedySolverBuilder::GreedySolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
    IHTCSolverBuilder(params, problemData, randGenerator, consumer)
{}

std::optional<GreedySolver> GreedySolverBuilder::prepareForBuild() const
{
    return GreedySolver(_problemData, _randGenerator, _consumer);
}
