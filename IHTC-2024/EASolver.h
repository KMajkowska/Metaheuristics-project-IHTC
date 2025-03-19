#pragma once

#include <random>

#include "IHTCSolver.h"
#include "ISelector.h"
#include "IProblem.h"
#include "ICIndividualConsumer.h"

/**
 * @brief Potential solver for solving the problem by evolutionary algorithm.
*/
class EASolver : public IHTCSolver
{
public:
	EASolver(const ProblemData& problemData, const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator, ICIndividualConsumer& consumer);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const override;

private:
	const ISelector& _selector;
	const IMutator& _mutator;
	const ICrosser& _crosser;
};