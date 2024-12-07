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
#include "IHTCMutatorNurseRoomCover.h"
#include "IHTCMutatorOT.h"
#include "IHTCMutatorDay.h"
#include "NeighbourGeneratorQueue.h"
#include "NeighbourGeneratorTournament.h"
#include "GreedySolver.h"
#include "IHTCMutatorNurseRoomCover.h"
#include "params.h"
#include "NeighbourGeneratorPrizeBest.h"
#include "NeighbourGeneratorTop.h"
#include "StopCriteriumTemperature.h"
#include "SimplexCoolingScheme.h"
#include "GemanAndGemanCoolingScheme.h"
#include "IHTCMutatorAssignment.h"
#include "IHTCMutatorOT.h"

IHTCSolver* getSolver(SolverType solverType, SASolver& saSolver, RandomSolver& randSolver, GreedySolver& greedySolver)
{
	switch (solverType) 
	{
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

	std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorRoom>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorDay>(randomGenerator, problemData, params.mutationProbability),
		std::make_shared<IHTCMutatorAssignment>(randomGenerator, problemData, params.mutationProbability),
	};

	if (problemData.getOperatingTheaters().size() > 1 && problemData.getPatients().size() > 1)
	{
		mutators.push_back(
			std::make_shared<IHTCMutatorOT>(randomGenerator, problemData, params.mutationProbability)
		);
	}

	NeighbourGeneratorQueue neighbourGenQueue(mutators, problem);
	NeighbourGeneratorTournament neighbourGenTournament(mutators, problem);
	NeighbourGeneratorPrizeBest neighbourGenPrize(mutators, problem, params.prizeSize);
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

	TemperatureOperator tempOperator(coolingScheme, params.increaseTempIters);

	GenderGrouper genderGrouper(params.genderGrouperIter, problemData, randomGenerator);
	IHTCMutatorNurseRoomCover nurseRoomCover(randomGenerator, problemData, params.mutationProbability);

	RandomSolver randomSolver(problemData, randomGenerator, logger);
	GreedySolver greedySolver(problemData, randomGenerator, logger);
	SASolver simulatedAnnealingSolver(
		problemData,
		params.startingTemperature,
		tempOperator,
		randomGenerator,
		stopCriterium,
		params.neighbourNumber,
		*generator,
		logger,
		genderGrouper,
		nurseRoomCover
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
