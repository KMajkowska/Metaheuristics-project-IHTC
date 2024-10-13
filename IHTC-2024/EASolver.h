#pragma once

#include <random>

#include "ISolver.h"

class EASolver : public ISolver
{
public:
	EASolver(const ISelector& selector, const IMutator& mutator, const ICrosser& crosser, std::mt19937& randGenerator);

	std::vector<CIndividual> solve(const ProblemData& problemData, const Problem& problem) const;

private:
	const ISelector& selector;
	const IMutator& mutator;
	const ICrosser& crosser;
	std::mt19937& randGenerator;
};