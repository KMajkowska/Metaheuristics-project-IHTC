#include <iostream>
#include <random>

#include "IHTCProblemIO.h"
#include "RandomSolver.h"
#include "RandomProblem.h"
#include "other.h"
#include "solutionUtils.h"

static const std::string PROBLEM_FILE = "../toy/toy.json";
static const std::string OUTPUT_FILE = "../solution.json";
static const std::string SOLUTION_FILE = "../toy/toy_solution.json";

int main(int argc, char* argv[])
{
	std::mt19937& mt = createRandomGenerator();

	RandomProblem problem(mt);

	RandomSolver solver(mt);

	try
	{
		ProblemData problemData = IHTCProblemIO::parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);

		SolutionData solutionDataTest = IHTCProblemIO::parseFromJSONSolution(argc > 1 ? argv[0] : SOLUTION_FILE);

		ViolatedRestrictions res = getViolatedFromSolution(problemData, solutionDataTest);

		const CIndividual& individual = solver.solve(problemData, problem);

		SolutionData solutionData = IHTCProblemIO::parseToSolution(individual, problemData);

		std::string solutionJson = IHTCProblemIO::parseSolutionToJSON(solutionData);

		writeToFile(OUTPUT_FILE, solutionJson);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
