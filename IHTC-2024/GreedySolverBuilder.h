#pragma once

#include "IHTCSolverBuilder.h"
#include "GreedySolver.h"

class GreedySolverBuilder : public IHTCSolverBuilder
{
public:
	GreedySolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

protected:
	std::optional<std::shared_ptr<IHTCSolver>> prepareForBuild() const override;
};