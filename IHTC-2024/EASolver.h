#pragma once

#include <random>

#include "IHTCSolver.h"
#include "ISelector.h"
#include "IProblem.h"

class EASolver : public IHTCSolver
{
public:
	EASolver(const ProblemData& problemData, const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator, Logger& logger);

	CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const;

	std::string getCSVHeaders() const;

private:
	const ISelector& selector;
	const IMutator& mutator;
	const ICrosser& crosser;
};