#include "SASolver.h"

SASolver::SASolver(
	const ProblemData& problemData,
	double startingTemp,
	std::shared_ptr<TemperatureOperator> tempOperator,
	std::mt19937& randGenerator,
	std::shared_ptr<IStopCriterium> stopCriterium,
	int neighbourhoodNumber,
	std::shared_ptr<INeighbourGenerator> neighbourGenerator,
	ICIndividualConsumer& consumer,
	GenderGrouper genderGrouper,
	IHTCMutatorNurseRoomCover nurseRoomCover
) :
	IHTCSolver(problemData, randGenerator, consumer),
	_startingTemp(startingTemp),
	_tempOperator(tempOperator),
	_stopCriterium(stopCriterium),
	_neighbourhoodNumber(neighbourhoodNumber),
	_neighbourGenerator(neighbourGenerator),
	_genderGrouper(genderGrouper),
	_nurseRoomCover(nurseRoomCover)
{}

CIndividual SASolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	double actualTemp = _startingTemp;
	int iteration = 0;

	CIndividual curr = startingIndividual;
	auto res = problem.eval(curr);
	curr.setFitness(res);

	CIndividual best = curr;

	while (!_stopCriterium->isStop(actualTemp, iteration))
	{
			std::vector<CIndividual> neighbours = _neighbourGenerator->getNeighbours(iteration, _neighbourhoodNumber, curr);

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

			if (iteration % _genderGrouper.iter() == 0 && curr.fitness().second.countGenderMixHard() > 0)
			{
				_genderGrouper.greedyGroupGenders(curr);
				curr.setFitness(problem.eval(curr));
				if (curr.fitness().first < best.fitness().first)
				{
					best = curr;
				}
			}

			if (iteration % _genderGrouper.iter() == 0 && curr.fitness().second.countUncoveredRoomHard() > 0)
			{
				_nurseRoomCover.mutate(curr);
				curr.setFitness(problem.eval(curr));
				if (curr.fitness().first < best.fitness().first)
				{
					best = curr;
				}
			}

			_consumer.consume(curr, best, actualTemp);
		}

		actualTemp = _tempOperator->getNewTemp(_startingTemp, actualTemp, iteration, curr.fitness().second);
		++iteration;
	}

	return best;
}

bool SASolver::checkIfAcceptNeighbour(const CIndividual& curr, const CIndividual& neighbour, double temperature) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	auto neighbourFitness { neighbour.fitness().first };
	auto currFitness { curr.fitness().first };

	auto diff { neighbourFitness - currFitness };

	while (diff > _startingTemp * NORMALIZATION_DIVIDER)
	{
		diff /= NORMALIZATION_DIVIDER;
	}

	double expCalc { exp(diff / temperature) };
	double expProb { 2 / (1 + expCalc) };

	return distribution(_randGenerator) < expProb;
}
