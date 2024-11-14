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

static const std::string PROBLEM_FILE = "../competition_instances/i03.json";
// static const std::string OUTPUT_FILE = "../solution.json";
// static const std::string SOLUTION_FILE = "../toy/toy_solution.json";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr int REPETITIONS = 1;

static constexpr int MAX_ITER = 250;
static constexpr double STARTING_TEMP = 800;  // 150 for VCF, 9 for GG, simplex is whatever
static constexpr int NEIGHBOURHOOD_NUMBER = 30;

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
	return currTemp < 0.1;
}

static bool stopCriteriumSAIter(double currTemp, int iteration)
{
	return iteration >= MAX_ITER;
}

static double variableCoolingFactorCoolingSchemeParam(double startingTemp, double currTemp, int iteration)
{
	return variableCoolingFactorCoolingScheme(startingTemp, currTemp, iteration, MAX_ITER);
}

static void run(int argc, char* argv[])
{
	std::string problemFile = argc > 1 ? argv[1] : PROBLEM_FILE;

	ProblemData problemData = IHTCProblemIO::parseFromJSON(problemFile);
	IHTCProblem problem(problemData, getViolatedFromSolution, calculateFitnessWithWeigtht);

	Logger logger(getLoggerFileName(problemFile));

	std::mt19937 mt = createRandomGenerator();

	const std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorOTSwap>(mt, problemData, NEIGHBOUR_PROB),
		std::make_shared<IHTCMutatorOTInversion>(mt, problemData, NEIGHBOUR_PROB),
		std::make_shared<IHTCMutatorRoom>(mt, problemData, NEIGHBOUR_PROB),
		std::make_shared<IHTCMutatorDay>(mt, problemData, NEIGHBOUR_PROB),
		std::make_shared<IHTCMutatorAssignmentsSwap>(mt, problemData, NEIGHBOUR_PROB)
	};

	NeighbourGeneratorQueue neighbourGenQueue(mutators, problem);
	NeighbourGeneratorTournament neighbourGenTournament(mutators, problem);

	RandomSolver randSolver(problemData, mt);
	GreedySolver greedySolver(problemData, mt, logger);
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

int main(int argc, char* argv[])
{
	try
	{
		run(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
