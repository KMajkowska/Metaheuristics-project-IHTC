#include <iostream>
#include <random>

#include <boost/asio.hpp>

#include "RandomSolver.h"
#include "other.h"
#include "solutionUtils.h"
#include "IHTCProblem.h"
#include "SASolver.h"
#include "IHTCMutatorRoom.h"
#include "IHTCMutatorOTInversion.h"
#include "IHTCMutatorNurseRoomCover.h"
#include "IHTCMutatorOT.h"
#include "IHTCMutatorDay.h"
#include "NeighbourGeneratorQueue.h"
#include "NeighbourGeneratorTournament.h"
#include "GreedySolver.h"
#include "params.h"
#include "NeighbourGeneratorPrizeBest.h"
#include "NeighbourGeneratorTop.h"
#include "StopCriteriumTemperature.h"
#include "SimplexCoolingScheme.h"
#include "GemanAndGemanCoolingScheme.h"
#include "IHTCMutatorAssignment.h"
#include "JSONOperations.h"
#include "SASolverBuilder.h"
#include "GreedySolverBuilder.h"
#include "CIndividualObservable.h"
#include "PeerToPeer.h"
#include "JSONSerializableExchanger.h"
#include "CSolutionDataHandler.h"


static void run(int argc, char* argv[])
{
	auto sendPort { argc > 1 ? (short)atoi(argv[1])  : 5000} ;
	auto recievePort { argc > 2 ? (short)atoi(argv[2]) : 5001};

	auto problemDataOpt = jsonToObject<ProblemData>(DEFAULT_PROBLEM_FILE);
	auto paramsOpt = jsonToObject<Params>(DEFAULT_PARAMS_FILE);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	auto peer { std::make_shared<PeerToPeer>("127.0.0.1", sendPort, recievePort) };

	peer->addObserver([](std::string observed)
		{
			std::cout << observed << std::endl;
		});

	CSolutionDataHandler exchanger(peer);
	// ICIndividualCSVLogger logger(params.outputPath() + getFileNameWithoutExtension(problemFile) + ".csv");

	peer->start();

	CIndividualObservable consumer(exchanger, problemData);

	std::mt19937 randomGenerator = createRandomGenerator();

	FitnessCalculator fitnessCalculator(params.hardRestrictionWeight());
	IHTCProblem problem(problemData, getViolatedFromSolution, fitnessCalculator);

	auto initSolver { GreedySolverBuilder(params, problemData, randomGenerator, consumer).build() };
	auto currentSolver { SASolverBuilder(params, problemData, randomGenerator, consumer, problem).build() };

	CIndividual startingIndividual = initSolver.solve(problem, CIndividual());

	const CIndividual& individual = currentSolver.solve(problem, startingIndividual);

	// evaluateProblem(params.solverRepetitionAmount(), problem, currentSolver, initSolver);
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

		return 1;
	}

	return 0;
}
