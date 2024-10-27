#include <iostream>
#include <random>

#include "IHTCProblemIO.h"
#include "RandomSolver.h"
#include "other.h"
#include "solutionUtils.h"
#include "IHTCProblem.h"
#include "SASolver.h"
#include "IHTCMutator.h"
#include "Logger.h"

static const std::string PROBLEM_FILE = "../toy/toy.json";
static const std::string OUTPUT_FILE = "../solution.json";
static const std::string SOLUTION_FILE = "../toy/toy_solution.json";
static const std::string LOG_FILE = "../logFile.txt";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr int REPETITIONS = 100;

static constexpr double STARTING_TEMP = 3000;
static constexpr int NEIGHBOURHOOD_NUMBER = 5;
static constexpr double DAY_CHANGE_PROB = 0.5;
static constexpr double ROOM_CHANGE_PROB = 0.2;

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

		IHTCMutator ihtcMutator(mt, problemData, DAY_CHANGE_PROB, ROOM_CHANGE_PROB);

		SASolver saSolver(
			problemData,
			STARTING_TEMP,
			calculateNewTemp,
			mt,
			stopCriteriumSA,
			NEIGHBOURHOOD_NUMBER,
			ihtcMutator
		);

		// Random does not need an initialized Individual
		CIndividual startingIndividual = randSolver.solve(problem, CIndividual());

		std::cout << evaluateProblem(REPETITIONS, problem, randSolver, startingIndividual) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
