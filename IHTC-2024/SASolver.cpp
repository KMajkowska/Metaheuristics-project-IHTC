#include "SASolver.h"

SASolver::SASolver(
	const ProblemData& problemData,
	double startingTemp,
	const ICoolingScheme& coolingScheme,
	std::mt19937& randGenerator,
	const IStopCriterium& stopCriterium,
	int neighbourhoodNumber,
	INeighbourGenerator& neighbourGenerator,
	Logger& logger
) :
	IHTCSolver(problemData, randGenerator, logger),
	startingTemp(startingTemp),
	coolingScheme(coolingScheme),
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

	while (!stopCriterium.isStop(actualTemp, iteration))
	{

		std::vector<CIndividual> neighbours = neighbourGenerator.getNeighbours(iteration, neighbourhoodNumber, curr);

		double bestNeighbour = DBL_MAX;
		double worstNeighbour = -1;
		std::vector<double> fitnesses;
		fitnesses.reserve(neighbours.size());

		for (auto& neighbour : neighbours)
		{
			if (!neighbour.isFitnessUpToDate())
			{
				neighbour.setFitness(problem.eval(neighbour));
			}

			double fitness = neighbour.getFitness().first;

			if (fitness < bestNeighbour)
			{
				bestNeighbour = fitness;
			}

			if (fitness > worstNeighbour)
			{
				worstNeighbour = fitness;
			}

			fitnesses.push_back(fitness);
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

				logger.log(
					curr.getFitness().second.getCSVData() + "," + std::to_string(curr.getFitness().first) + "," +
					best.getFitness().second.getCSVData() + "," + std::to_string(best.getFitness().first) + "," +
					std::to_string(actualTemp) + "," +
					std::to_string(worstNeighbour) + "," +
					std::to_string(bestNeighbour) + "," +
					std::to_string(calcAverage(fitnesses)) + "," +
					std::to_string(calcStdDev(fitnesses)) + "," +
					curr.getMutatorName()
				);
			}
		}

		actualTemp = coolingScheme.getNewTemp(startingTemp, actualTemp, iteration);
		++iteration;
	}

	return best;
}

std::string SASolver::getCSVHeaders() const
{
	ViolatedRestrictions res;

	return res.getCSVColumns("") + ",res," + res.getCSVColumns("Best") + ",resBest,actualTemp,worstNeighbour,bestNeighbour,avgNeighbour,stdDevNeighbour,currMutator";
}

bool SASolver::checkIfAcceptNeighbour(const CIndividual& curr, const CIndividual& neighbour, double temperature) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	int neighbourFitness = neighbour.getFitness().first;
	int currFitness = curr.getFitness().first;

	int diff = neighbourFitness - currFitness;

	while (diff > startingTemp * NORMALIZATION_DIVIDER)
	{
		diff /= NORMALIZATION_DIVIDER;
	}

	double expCalc = exp(diff / temperature);
	double expProb = 2 / (1 + expCalc);

	// logger.log(std::to_string(expProb));

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

