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


CIndividual getToyCIndividual()
{
	const std::string r0 = "r0";
	const std::string r1 = "r1";
	const std::string r2 = "r2";

	const std::string early = "early";
	const std::string late = "late";
	const std::string night = "night";

	const std::string t0 = "t0";

	std::vector<Patient> patients
	{
		Patient(4, r2, t0),
		Patient(4, r2, t0),
		Patient(4, r1, t0),
		Patient(4, r2, t0),
		Patient(4, r0, t0),
		Patient(1, r0, t0),
		Patient(4, r2, t0)
	};

	std::vector<std::vector<Assignment>> assignments
	{
		{
			{
				Assignment(0, late, { r2 }),
				Assignment(3, late, { }),
				Assignment(5, night, { }),
			},
			{
				Assignment(1, night, { }),
				Assignment(4, late, { r0 }),
				Assignment(6, night, { }),
			},
			{
				Assignment(0, late, { }),
				Assignment(2, early, { }),
				Assignment(3, early, { r0 }),
				Assignment(4, late, { }),
				Assignment(6, late, { }),
			},
			{
				Assignment(0, early, { r2 }),
				Assignment(1, night, { r0 }),
				Assignment(3, early, { r1 }),
				Assignment(4, night, { r0, r1, r2 }),
				Assignment(5, night, { r0, r1, r2 }),
				Assignment(6, night, { r0, r1, r2 }),
			},
			{
				Assignment(0, late, { }),
				Assignment(2, early, { r2 }),
				Assignment(3, early, { r2 }),
				Assignment(4, early, { }),
				Assignment(5, late, { r0, r1, r2 }),
				Assignment(6, late, { r0, r1, r2 }),
			},
			{
				Assignment(0, early, { r0 }),
				Assignment(1, early, { r0, r1, r2 }),
				Assignment(2, early, { r0, r1 }),
				Assignment(6, late, { }),
			},
			{
				Assignment(0, late, { r0, r1 }),
				Assignment(1, late, { r0, r1, r2 }),
				Assignment(2, night, { r0 }),
			},
			{
				Assignment(0, late, { }),
				Assignment(1, night, { r1, r2, }),
				Assignment(2, night, { }),
				Assignment(3, night, { r0, r1, r2 }),
				Assignment(5, late, { }),
			},
			{
				Assignment(0, late, { }),
				Assignment(2, early, { }),
				Assignment(4, early, { r0, r1, r2 }),
				Assignment(5, early, { r0, r1, r2 }),
				Assignment(6, early, { r0, r1, r2 }),
			},
			{
				Assignment(0, early, { r1 }),
				Assignment(2, late, { r0, r1, r2 }),
				Assignment(3, late, { r0, r1, r2 }),
				Assignment(4, late, { r1, r2 }),
				Assignment(5, late, {}),
			},
			{
				Assignment(0, night, { r0, r1, r2 }),
				Assignment(2, night, { r1, r2 }),
				Assignment(4, late, { }),
				Assignment(6, early, { }),
			},
		}
	};

	return CIndividual(patients, assignments);
}

int main(int argc, char* argv[])
{
	std::mt19937& mt = createRandomGenerator();

	RandomProblem problem(mt);

	RandomSolver solver(mt);

	IHTCProblemIO problemIO;

	try
	{
		ProblemData problemData = problemIO.parseFromJSON(argc > 1 ? argv[0] : PROBLEM_FILE);

		SolutionData solutionDataTest = problemIO.parseFromJSONSolution(argc > 1 ? argv[0] : SOLUTION_FILE);

		ViolatedRestrictions res = getViolatedFromSolution(problemData, solutionDataTest);

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
