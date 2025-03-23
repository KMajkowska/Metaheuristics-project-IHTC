#pragma once

#include "IHTCSolverBuilder.h"
#include "SASolver.h"
#include "solverUtils.h"

class SASolverBuilder : public IHTCSolverBuilder
{
public:
	SASolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer, const IProblem& problem);

protected:
	std::optional<std::shared_ptr<IHTCSolver>> prepareForBuild() const override;

private:
	const IProblem& _problem;
	const Params& _params;
};