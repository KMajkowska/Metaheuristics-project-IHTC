#include <iostream>
#include <random>

#include "IHTCProblemIO.h"
#include "RandomSolver.h"
#include "other.h"
#include "solutionUtils.h"
#include "IHTCProblem.h"
#include "SASolver.h"
#include "Logger.h"
#include "IHTCMutatorRoom.h"
#include "IHTCMutatorOTInversion.h"
#include "IHTCMutatorOTSwap.h"
#include "IHTCMutatorDay.h"
#include "NeighbourGeneratorQueue.h"
#include "NeighbourGeneratorTournament.h"
#include "GreedySolver.h"
#include "IHTCMutatorAssignmentsSwap.h"
	
static const std::string PROBLEM_FILE = "../competition_instances/i01.json";
// static const std::string OUTPUT_FILE = "../solution.json";
// static const std::string SOLUTION_FILE = "../toy/toy_solution.json";
static const std::string LOG_FILE = "../logFile.txt";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr int REPETITIONS = 1;

static constexpr int MAX_ITER = 250;
static constexpr double STARTING_TEMP = 800;  // 150 for VCF, 9 for GG, simplex is whatever
static constexpr int NEIGHBOURHOOD_NUMBER = 5;

static constexpr double NEIGHBOUR_PROB = 1;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << "{";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		os << vec[i];

		if (i != vec.size() - 1)
		{
			os << ", ";
		}
	}

	os << "}\n";

	return os;
}

static double calculateFitnessWithWeigtht(const WeightsDTO& weights, const ViolatedRestrictions& restrictions)
{
	return calculateFitness(HARD_RESTRICTION_WEIGHT, weights, restrictions);
}

static bool stopCriteriumSA(double currTemp, int iteration)
{
	return currTemp < 1.0;
}

static bool stopCriteriumSAIter(double currTemp, int iteration)
{
	return iteration >= MAX_ITER;
}

static double variableCoolingFactorCoolingSchemeParam(double startingTemp, double currTemp, int iteration)
{
	return variableCoolingFactorCoolingScheme(startingTemp, currTemp, iteration, MAX_ITER);
}

int main(int argc, char* argv[])
{
	std::mt19937 mt = createRandomGenerator();

	Logger logger(LOG_FILE);

	try
	{
		ProblemData problemData = IHTCProblemIO::parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);

		IHTCProblem problem(problemData, getViolatedFromSolution, calculateFitnessWithWeigtht);

		RandomSolver randSolver(problemData, mt);

		GreedySolver greedySolver(problemData, mt, logger);

		const std::vector<std::shared_ptr<IMutator>> mutators =
		{
			std::make_shared<IHTCMutatorOTSwap>(mt, problemData, NEIGHBOUR_PROB),
			std::make_shared<IHTCMutatorOTInversion>(mt, problemData, NEIGHBOUR_PROB),
			std::make_shared<IHTCMutatorRoom>(mt, problemData, NEIGHBOUR_PROB),
			std::make_shared<IHTCMutatorDay>(mt, problemData, NEIGHBOUR_PROB),
			std::make_shared<IHTCMutatorAssignmentsSwap>(mt, problemData, NEIGHBOUR_PROB)
		};

		NeighbourGeneratorQueue neighbourGenQueue(mutators);
		NeighbourGeneratorTournament neighbourGenTournament(mutators);

		SASolver saSolver(
			problemData,
			STARTING_TEMP,
			simplexCoolingScheme,
			mt,
			stopCriteriumSA,
			NEIGHBOURHOOD_NUMBER,
			neighbourGenTournament,
			logger
		);

		evaluateProblem(REPETITIONS, problem, saSolver, greedySolver);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
