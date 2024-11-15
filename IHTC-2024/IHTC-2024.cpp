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
#include "IHTCMutatorNurseRoomCover.h"
#include "params.h"

static void run(int argc, char* argv[])
{
	std::string problemFile = argc > 1 ? argv[1] : DEFAULT_PROBLEM_FILE;

	Logger logger(getLoggerFileName(problemFile));

	ProblemData problemData = IHTCProblemIO::parseFromJSON(problemFile);
	IHTCProblem problem(problemData, getViolatedFromSolution, calculateFitnessWithWeigtht);

	std::mt19937 randomGenerator = createRandomGenerator();

	const std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorOTSwap>(randomGenerator, problemData, MUTATION_PROBABILITY),
		std::make_shared<IHTCMutatorOTInversion>(randomGenerator, problemData, MUTATION_PROBABILITY),
		std::make_shared<IHTCMutatorRoom>(randomGenerator, problemData, MUTATION_PROBABILITY),
		std::make_shared<IHTCMutatorDay>(randomGenerator, problemData, MUTATION_PROBABILITY),
		std::make_shared<IHTCMutatorAssignmentsSwap>(randomGenerator, problemData, MUTATION_PROBABILITY),
		std::make_shared<IHTCMutatorNurseRoomCover>(randomGenerator, problemData, MUTATION_PROBABILITY)
	};

	NeighbourGeneratorQueue neighbourGenQueue(mutators, problem);
	NeighbourGeneratorTournament neighbourGenTournament(mutators, problem);

	RandomSolver randomSolver(problemData, randomGenerator, logger);
	GreedySolver greedySolver(problemData, randomGenerator, logger);
	SASolver simulatedAnnealingSolver(
		problemData,
		STARTING_TEMPERATURE,
		simplexCoolingScheme,
		randomGenerator,
		stopCriteriumSA,
		NEIGHBOUR_NUMBER,
		neighbourGenTournament,
		logger
	);

	const auto& currentSolver = simulatedAnnealingSolver;

	logger.log(currentSolver.getCSVHeaders());

	evaluateProblem(SOLVER_REPETITION_AMOUNT, problem, currentSolver, randomSolver);
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

	return 0;
}
