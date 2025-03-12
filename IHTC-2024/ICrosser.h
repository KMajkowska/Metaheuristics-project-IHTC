#pragma once
#include<vector>

class CIndividual;

/**
 * @brief Class used as interface to cross our individuals. Used for EA solver
*/
class ICrosser
{
public:
	virtual std::vector<CIndividual> crossover(const CIndividual& parent1, const CIndividual& parent2) const = 0;
};