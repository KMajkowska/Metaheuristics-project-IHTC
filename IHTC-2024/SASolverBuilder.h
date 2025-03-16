#pragma once

#include "IHTCSolverBuilder.h"
#include "SASolver.h"
#include "solverUtils.h"

class SASolverBuilder : public IHTCSolverBuilder<SASolver>
{
public:
	SASolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer, const IProblem& problem);

protected:
	std::optional<SASolver> prepareForBuild() const override;

private:
	const IProblem& _problem;
};