#pragma once

#include <random>

#include "ISolver.h"
#include "ISelector.h"
#include "IProblem.h"

class EASolver : public ISolver
{
public:
	EASolver(const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator);

	CIndividual solve(const ProblemData& problemData, const IProblem& problem) const;

private:
	const ISelector& selector;
	const IMutator& mutator;
	const ICrosser& crosser;
	std::mt19937& randGenerator;
};