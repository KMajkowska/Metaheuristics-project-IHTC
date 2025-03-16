#include "SASolver.h"

SASolver::SASolver(
	const ProblemData& problemData,
	double startingTemp,
	TemperatureOperator& tempOperator,
	std::mt19937& randGenerator,
	const IStopCriterium& stopCriterium,
	int neighbourhoodNumber,
	INeighbourGenerator& neighbourGenerator,
	ICIndividualConsumer& consumer,
	const GenderGrouper& genderGrouper,
	const IHTCMutatorNurseRoomCover& nurseRoomCover
) :
	IHTCSolver(problemData, randGenerator, consumer),
	startingTemp(startingTemp),
	tempOperator(tempOperator),
	stopCriterium(stopCriterium),
	neighbourhoodNumber(neighbourhoodNumber),
	neighbourGenerator(neighbourGenerator),
	genderGrouper(genderGrouper),
	nurseRoomCover(nurseRoomCover)
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

		if (neighbours.empty())
		{
			continue;
		}

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

			double fitness = neighbour.fitness().first;

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
			if (neighbour.fitness().first < curr.fitness().first || checkIfAcceptNeighbour(curr, neighbour, actualTemp))
			{
				curr = neighbour;

				if (curr.fitness().first < best.fitness().first)
				{
					best = curr;
				}

			}

			if (iteration % genderGrouper.getIter() == 0 && curr.fitness().second.countGenderMixHard > 0)
			{
				genderGrouper.greedyGroupGenders(curr);
				curr.setFitness(problem.eval(curr));
				if (curr.fitness().first < best.fitness().first)
				{
					best = curr;
				}
			}

			if (iteration % genderGrouper.getIter() == 0 && curr.fitness().second.countUncoveredRoomHard > 0)
			{
				nurseRoomCover.mutate(curr);
				curr.setFitness(problem.eval(curr));
				if (curr.fitness().first < best.fitness().first)
				{
					best = curr;
				}
			}

			consumer.consume(curr, best, actualTemp);
		}

		actualTemp = tempOperator.getNewTemp(startingTemp, actualTemp, iteration, curr.fitness().second);
		++iteration;
	}

	return best;
}

bool SASolver::checkIfAcceptNeighbour(const CIndividual& curr, const CIndividual& neighbour, double temperature) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	int neighbourFitness = neighbour.fitness().first;
	int currFitness = curr.fitness().first;

	int diff = neighbourFitness - currFitness;

	while (diff > startingTemp * NORMALIZATION_DIVIDER)
	{
		diff /= NORMALIZATION_DIVIDER;
	}

	double expCalc = exp(diff / temperature);
	double expProb = 2 / (1 + expCalc);

	return distribution(randGenerator) < expProb;
}