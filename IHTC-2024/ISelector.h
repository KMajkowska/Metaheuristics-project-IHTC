#pragma once
#include<vector>

class CIndividual;

/**
 * @brief Class used as an interface to provide polymorphism for different ways of slecting our neighbours to next generation. Used for EASolver
*/
class ISelector
{
public:
	virtual std::vector<CIndividual> select(std::vector<CIndividual> population) const = 0;
};