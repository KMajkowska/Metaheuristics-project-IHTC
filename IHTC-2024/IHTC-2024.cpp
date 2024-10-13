#include <iostream>
#include <random>

#include "IHTCProblemIO.h"
#include "RandomSolver.h"
#include "RandomProblem.h"
#include "other.h"

static const std::string PROBLEM_FILE = "../toy/toy.json";
static const std::string OUTPUT_FILE = "../solution.json";

int main(int argc, char* argv[])
{
	std::mt19937& mt = createRandomGenerator();
	RandomProblem problem(mt);

	RandomSolver solver(mt);

	IHTCProblemIO problemIO;

	try
	{
		ProblemData problemData = problemIO.parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);

		const CIndividual& individual = solver.solve(problemData, problem);

		SolutionData solutionData = problemIO.parseToSolution(individual, problemData);

		std::string solutionJson = problemIO.parseSolutionToJSON(solutionData);

		writeToFile(OUTPUT_FILE, solutionJson);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}
