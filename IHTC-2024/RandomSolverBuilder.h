#pragma once

#include "IHTCSolverBuilder.h"
#include "RandomSolver.h"

/**
 * @brief Builder of random solver
*/
class RandomSolverBuilder : public IHTCSolverBuilder
{
public:
	RandomSolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

protected:
	std::optional<std::shared_ptr<IHTCSolver>> prepareForBuild() const override;
};