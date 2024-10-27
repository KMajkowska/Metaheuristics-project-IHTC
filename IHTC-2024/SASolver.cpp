#include "SASolver.h"

SASolver::SASolver(
		const ProblemData& problemData,
		double startingTemp, 
		std::function<double(double, int)> coolingFn, 
		std::mt19937& randGenerator, 
		std::function<bool(double, int)>  stopCriterium, 
		int neighbourhoodNumber, 
		const IMutator& mutator
):
		IHTCSolver(problemData, randGenerator),
		startingTemp(startingTemp),
		coolingFn(coolingFn),
		stopCriterium(stopCriterium),
		neighbourhoodNumber(neighbourhoodNumber),
		mutator(mutator)
{}

CIndividual SASolver::solve(const IProblem & problem, const CIndividual& startingIndividual) const
{
	double actualTemp = startingTemp;
	int iteration = 0;

	CIndividual individual = startingIndividual;
	individual.setFitness(problem.eval(individual));

	while (!stopCriterium(actualTemp, iteration))
	{
		std::vector<CIndividual> neighbours = individual.createNeighbours(mutator, neighbourhoodNumber);
		for (auto& neighbour : neighbours) 
		{
			neighbour.setFitness(problem.eval(neighbour));
		}

		for (auto& neighbour : neighbours)
		{
			if (neighbour.getFitness() > individual.getFitness() || checkIfAcceptNeighbour(individual, neighbour, actualTemp))
			{
				individual = std::move(neighbour);
			}
		}

		actualTemp = coolingFn(actualTemp, iteration);
		++iteration;
	}
	
	return individual;
}

bool SASolver::checkIfAcceptNeighbour(const CIndividual& individual, const CIndividual& neighbour, double temperature) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	return distribution(randGenerator) < exp((neighbour.getFitness() - individual.getFitness()) / temperature);
}

/*
* procedure simulated_annealing
begin
t←0; poczatkowa temperatura T; losowy wybór vc; ocena vc
repeat
 repeat
 wybór Vn z sasiadów w zmianie pojedynczej cechy vc //próbkowanie poprzez inversję lub swap
 if f(Vc) < f(Vn) then Vc ← Vn
 else if random[0,1] < exp{(f(Vn)– f(Vc))/T}
 then Vc ← Vn
 until (warunek konca)
T ← g(T,t)
t ← t+1
until (kryterium_stopu)
end
*/

