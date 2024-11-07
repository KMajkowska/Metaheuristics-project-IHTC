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

static const std::string PROBLEM_FILE = "../competition_instances/i10.json";
//static const std::string OUTPUT_FILE = "../solution.json";
//static const std::string SOLUTION_FILE = "../toy/toy_solution.json";
static const std::string LOG_FILE = "../logFile.txt";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr int REPETITIONS = 100;

static constexpr int MAX_ITER = 250;
static constexpr double STARTING_TEMP = 150;  // 150 for VCF, 9 for GG, simplex is whatever
static constexpr int NEIGHBOURHOOD_NUMBER = 15;

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

	logger.log(ViolatedRestrictions().getCSVColumns() + ",res");

	try
	{
		ProblemData problemData = IHTCProblemIO::parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);
		
		IHTCProblem problem(problemData, getViolatedFromSolution, calculateFitnessWithWeigtht, logger);

		RandomSolver randSolver(problemData, mt);

		IHTCMutatorOTSwap ihtcMutator(mt, problemData, NEIGHBOUR_PROB);

		IHTCMutatorOTInversion ihtMutatorOTInversion(mt, problemData, NEIGHBOUR_PROB);

		SASolver saSolver(
			problemData,
			STARTING_TEMP,
			variableCoolingFactorCoolingSchemeParam,
			mt,
			stopCriteriumSAIter,
			NEIGHBOURHOOD_NUMBER,
			ihtMutatorOTInversion
		);

		std::cout << evaluateProblem(REPETITIONS, problem, saSolver, randSolver) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
