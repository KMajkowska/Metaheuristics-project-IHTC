#pragma once

#include <random>

#include "CIndividual.h"
#include "ProblemData.h"

class GenderGrouper
{
public:
	GenderGrouper(int perIterAmountFix, const ProblemData& problemData, std::mt19937& randGenerator);

	void greedyGroupGenders(CIndividual& individual) const;

	int getIter() const;


private:
	int perIterAmountFix = 0;

	const ProblemData& problemData;
	std::mt19937& randGenerator;
};