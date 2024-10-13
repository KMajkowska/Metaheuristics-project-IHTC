#pragma once
#include<vector>

class CIndividual;

class ICrosser
{
public:
	virtual std::vector<CIndividual> crossover(const CIndividual& parent1, const CIndividual& parent2) const = 0;
};