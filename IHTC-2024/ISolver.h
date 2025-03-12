#pragma once
#include <vector>
#include <random>

#include "IProblem.h"
#include "ProblemData.h"
#include "CIndividual.h"

/**
 * @brief We use this class as an interface to provide polymorphism. 
 * 
 * As we can have many ways of solving problem of IHTC and initialazing SA, we use tgis class to have one, structures interface for all of the solver instances
 * _problemData is out problem, we want to solve.
 * _randGenerator is given random, which we want to use in every class using random generation.
*/
class ISolver
{
public:
	ISolver(const ProblemData& problemData, std::mt19937& randGenerator);
	/**
	 * @brief Every derived class of ISolver has its own implementation of this method. It basically makes another iteration (when SA Solver) or solve the whole problem by 
	 * assigning patients, rooms, nurses, surgeon and OTs
	 * @param problem the problem we want to solve
	 * @param startingIndividual algorithm individual which is our starting point to solve the whole problem
	 * @return individual, which is the solution
	*/
	virtual CIndividual solve(const IProblem& problem, const CIndividual& startingIndividual) const = 0;

protected:
	const ProblemData& _problemData;
	std::mt19937& _randGenerator;
};