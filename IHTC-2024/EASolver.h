#pragma once

#include <random>

#include "IHTCSolver.h"
#include "ISelector.h"
#include "IProblem.h"

class EASolver : public IHTCSolver
{
public:
	EASolver(const ProblemData& problemData, const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

private:
	const ISelector& selector;
	const IMutator& mutator;
	const ICrosser& crosser;
};