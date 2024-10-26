#include <iostream>
#include <random>

#include "IHTCProblemIO.h"
#include "RandomSolver.h"
#include "other.h"
#include "solutionUtils.h"
#include "IHTCProblem.h"

static const std::string PROBLEM_FILE = "../toy/toy.json";
static const std::string OUTPUT_FILE = "../solution.json";
static const std::string SOLUTION_FILE = "../toy/toy_solution.json";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr int REPETITIONS = 10000;

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

int main(int argc, char* argv[])
{
	std::mt19937 mt = createRandomGenerator();

	try
	{
		ProblemData problemData = IHTCProblemIO::parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);

		IHTCProblem problem(problemData, getViolatedFromSolution, calculateFitnessWithWeigtht);

		RandomSolver solver(problemData, mt);

		std::cout << evaluateProblem(REPETITIONS, problem, solver) << std::endl;

		/*
		SolutionData solutionDataTest = IHTCProblemIO::parseFromJSONSolution(argc > 1 ? argv[0] : SOLUTION_FILE);

		const CIndividual& individual = solver.solve(problem);

		SolutionData solutionData = IHTCProblemIO::parseToSolution(individual, problemData);

		std::string solutionJson = IHTCProblemIO::parseSolutionToJSON(solutionData);

		writeToFile(OUTPUT_FILE, solutionJson);
		*/
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
