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
#include "NeighbourGeneratorPrizeBest.h"
#include "NeighbourGeneratorTop.h"
#include "StopCriteriumTemperature.h"
#include "SimplexCoolingScheme.h"
#include "GemanAndGemanCoolingScheme.h"

IHTCSolver* getSolver(SolverType solverType, SASolver& saSolver, RandomSolver& randSolver, GreedySolver& greedySolver)
{
	switch (solverType) {
	case SolverType::SA:
		return &saSolver;
	case SolverType::RAND:
		return &randSolver;
	case SolverType::GREEDY:
		return &greedySolver;
	default:
		throw std::invalid_argument("Incorrect solver type");
	}
}

static void run(int argc, char* argv[])
{
	std::string problemFile = argc > 1 ? argv[1] : DEFAULT_PROBLEM_FILE;
	std::string paramsFile = argc > 2 ? argv[2] : DEFAULT_PARAMS_FILE;

	ProblemData problemData = IHTCProblemIO::parseFromJSON(problemFile);
	Params params = IHTCProblemIO::parseParamsFromJSON(paramsFile);

	Logger logger(params.outputPath + getFileNameWithoutExtension(problemFile) + ".csv");

	std::mt19937 randomGenerator = createRandomGenerator();

	FitnessCalculator fitnessCalculator(params.hardRestrictionWeight);
	StopCriteriumTemperature stopCriterium(params.stopTemperature);
	SimplexCoolingScheme coolingScheme(params.simplexCoolingMultiplier);
	GemanAndGemanCoolingScheme gemanCoolingScheme;

	IHTCProblem problem(problemData, getViolatedFromSolution, fitnessCalculator);

	const std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorOTSwap>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorOTInversion>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorRoom>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorDay>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorAssignmentsSwap>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorNurseRoomCover>(randomGenerator, problemData, params.mutationProbability)
	};

	NeighbourGeneratorQueue neighbourGenQueue(mutators, problem);
	NeighbourGeneratorTournament neighbourGenTournament(mutators, problem);
	NeighbourGeneratorPrizeBest neighbourGenPrize(mutators, problem);
	NeighbourGeneratorTop neighbourGenTop(mutators, problem);

	INeighbourGenerator* generator = nullptr;

	if (params.neighbourGenerator == NeighbourGeneratorType::TOURNAMENT)
	{
		generator = &neighbourGenTournament;
	}
	else if (params.neighbourGenerator == NeighbourGeneratorType::PRIZE_BEST)
	{
		generator = &neighbourGenPrize;
	}
	else if (params.neighbourGenerator == NeighbourGeneratorType::QUEUE)
	{
		generator = &neighbourGenQueue;
	}
	else if (params.neighbourGenerator == NeighbourGeneratorType::TOP)
	{
		generator = &neighbourGenTop;
	} 
	else
	{
		throw std::invalid_argument("Incorrect neighbour generator");
	}


	RandomSolver randomSolver(problemData, randomGenerator, logger);
	GreedySolver greedySolver(problemData, randomGenerator, logger);
	SASolver simulatedAnnealingSolver(
		problemData,
		params.startingTemperature,
		coolingScheme,
		randomGenerator,
		stopCriterium,
		params.neighbourNumber,
		*generator,
		logger
	);

	IHTCSolver* initSolver = getSolver(params.initSolver, simulatedAnnealingSolver, randomSolver, greedySolver);
	IHTCSolver* currentSolver = getSolver(params.outputSolver, simulatedAnnealingSolver, randomSolver, greedySolver);

	logger.log(currentSolver->getCSVHeaders());

	evaluateProblem(params.solverRepetitionAmount, problem, *currentSolver, *initSolver);
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
