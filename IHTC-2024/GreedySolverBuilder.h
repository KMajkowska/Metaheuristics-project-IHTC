#pragma once

#include "IHTCSolverBuilder.h"
#include "GreedySolver.h"

class GreedySolverBuilder : public IHTCSolverBuilder<GreedySolver>
{
public:
	GreedySolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

protected:
	std::optional<GreedySolver> prepareForBuild() const override;
};