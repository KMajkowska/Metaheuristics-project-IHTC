#include "SASolver.h"

SASolver::SASolver(
	const ProblemData& problemData,
	double startingTemp,
	std::function<double(double, double, int)> coolingFn,
	std::mt19937& randGenerator,
	std::function<bool(double, int)>  stopCriterium,
	int neighbourhoodNumber,
	INeighbourGenerator& neighbourGenerator,
	Logger& logger
) :
	IHTCSolver(problemData, randGenerator, logger),
	startingTemp(startingTemp),
	coolingFn(coolingFn),
	stopCriterium(stopCriterium),
	neighbourhoodNumber(neighbourhoodNumber),
	neighbourGenerator(neighbourGenerator)
{}

CIndividual SASolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	double actualTemp = startingTemp;
	int iteration = 0;

	CIndividual curr = startingIndividual;
	auto res = problem.eval(curr);
	curr.setFitness(res);

	CIndividual best = curr;

	logger.log(res.second.getCSVColumns("") + ",res," + res.second.getCSVColumns("Best") + ",resBest");

	while (!stopCriterium(actualTemp, iteration))
	{
		std::vector<CIndividual> neighbours = neighbourGenerator.getNeighbours(iteration, neighbourhoodNumber, curr);

		for (auto& neighbour : neighbours)
		{
			if (!neighbour.isFitnessUpToDate())
			{
				neighbour.setFitness(problem.eval(neighbour));
			}
		}

		for (const auto& neighbour : neighbours)
		{
			if (neighbour.getFitness().first < curr.getFitness().first || checkIfAcceptNeighbour(curr, neighbour, actualTemp))
			{
				curr = neighbour;

				if (curr.getFitness().first < best.getFitness().first)
				{
					best = curr;
				}
			}

			logger.log(
				curr.getFitness().second.getCSVData() + "," + std::to_string(curr.getFitness().first) + "," +
				best.getFitness().second.getCSVData() + "," + std::to_string(best.getFitness().first)
			);
		}

		actualTemp = coolingFn(startingTemp, actualTemp, iteration);
		++iteration;
	}

	return best;
}

bool SASolver::checkIfAcceptNeighbour(const CIndividual& curr, const CIndividual& neighbour, double temperature) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	int normalizedDiff = neighbour.getFitness().first - curr.getFitness().first;

	while (normalizedDiff > startingTemp * NORMALIZATION_DIVIDER)
	{
		normalizedDiff /= NORMALIZATION_DIVIDER;
	}

	double expCalc = exp(normalizedDiff / temperature);
	double expProb = 1 / (1 + expCalc);

	return distribution(randGenerator) < expProb;
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

