#pragma once

#include "IHTCSolverBuilder.h"
#include "RandomSolver.h"

class RandomSolverBuilder : public IHTCSolverBuilder<RandomSolver>
{
public:
	RandomSolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

protected:
	std::optional<RandomSolver> prepareForBuild() const override;
};