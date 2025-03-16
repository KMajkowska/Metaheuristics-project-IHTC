#include <iostream>
#include <random>

#include <boost/asio.hpp>

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
#include "params.h"
#include "NeighbourGeneratorPrizeBest.h"
#include "NeighbourGeneratorTop.h"
#include "StopCriteriumTemperature.h"
#include "SimplexCoolingScheme.h"
#include "GemanAndGemanCoolingScheme.h"
#include "IHTCMutatorAssignment.h"
#include "JSONOperations.h"


static IHTCSolver* getSolver(SolverType solverType, SASolver& saSolver, RandomSolver& randSolver, GreedySolver& greedySolver)
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

	auto problemDataOpt = jsonToObject<ProblemData>(problemFile);
	auto paramsOpt = jsonToObject<Params>(paramsFile);

	if (!problemDataOpt || !paramsOpt)
	{
		return;
	}

	auto problemData(std::move(problemDataOpt.value()));
	auto params(std::move(paramsOpt.value()));

	Logger logger(params.outputPath() + getFileNameWithoutExtension(problemFile) + ".csv");

	std::mt19937 randomGenerator = createRandomGenerator();

	FitnessCalculator fitnessCalculator(params.hardRestrictionWeight());
	StopCriteriumTemperature stopCriterium(params.stopTemperature());
	SimplexCoolingScheme coolingScheme(params.simplexCoolingMultiplier());
	GemanAndGemanCoolingScheme gemanCoolingScheme;

	IHTCProblem problem(problemData, getViolatedFromSolution, fitnessCalculator);

	std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorRoom>(randomGenerator, problemData, params.mutationProbability()),
		std::make_shared<IHTCMutatorDay>(randomGenerator, problemData, params.mutationProbability()),
		std::make_shared<IHTCMutatorAssignment>(randomGenerator, problemData, params.mutationProbability()),
	};

	if (problemData.operatingTheaters().size() > 1 && problemData.patients().size() > 1)
	{
		mutators.push_back(
			std::make_shared<IHTCMutatorOT>(randomGenerator, problemData, params.mutationProbability())
		);
	}

	NeighbourGeneratorQueue neighbourGenQueue(mutators, problem);
	NeighbourGeneratorTournament neighbourGenTournament(mutators, problem);
	NeighbourGeneratorPrizeBest neighbourGenPrize(mutators, problem, params.prizeSize());
	NeighbourGeneratorTop neighbourGenTop(mutators, problem);

	INeighbourGenerator* generator = nullptr;

	if (params.neighbourGenerator() == NeighbourGeneratorType::TOURNAMENT)
	{
		generator = &neighbourGenTournament;
	}
	else if (params.neighbourGenerator() == NeighbourGeneratorType::PRIZE_BEST)
	{
		generator = &neighbourGenPrize;
	}
	else if (params.neighbourGenerator() == NeighbourGeneratorType::QUEUE)
	{
		generator = &neighbourGenQueue;
	}
	else if (params.neighbourGenerator() == NeighbourGeneratorType::TOP)
	{
		generator = &neighbourGenTop;
	} 
	else
	{
		throw std::invalid_argument("Incorrect neighbour generator");
	}

	TemperatureOperator tempOperator(coolingScheme, params.increaseTempIters());

	GenderGrouper genderGrouper(params.genderGrouperIter(), problemData, randomGenerator);
	IHTCMutatorNurseRoomCover nurseRoomCover(randomGenerator, problemData, params.mutationProbability());

	RandomSolver randomSolver(problemData, randomGenerator, logger);
	GreedySolver greedySolver(problemData, randomGenerator, logger);
	SASolver simulatedAnnealingSolver(
		problemData,
		params.startingTemperature(),
		tempOperator,
		randomGenerator,
		stopCriterium,
		params.neighbourNumber(),
		*generator,
		logger,
		genderGrouper,
		nurseRoomCover
	);

	IHTCSolver* initSolver = getSolver(params.initSolver(), simulatedAnnealingSolver, randomSolver, greedySolver);
	IHTCSolver* currentSolver = getSolver(params.outputSolver(), simulatedAnnealingSolver, randomSolver, greedySolver);

	evaluateProblem(params.solverRepetitionAmount(), problem, *currentSolver, *initSolver);
}



void broadcastSession(short port) {
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
	socket.set_option(boost::asio::socket_base::broadcast(true));

	boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), port);

	while (true) {
		std::string message = "TicTacToeSession: 192.168.1.100:12345"; // Replace with actual IP
		socket.send_to(boost::asio::buffer(message), broadcast_endpoint);
		std::cout << "Broadcasting game session...\n";
		std::this_thread::sleep_for(std::chrono::seconds(2)); // Broadcast every 2 seconds
	}
}

void discoverSessions(short port) {
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));

	char buffer[1024];
	boost::asio::ip::udp::endpoint sender_endpoint;

	std::cout << "Listening for game sessions...\n";
	while (true) {
		size_t length = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
		std::string message(buffer, length);
		std::cout << "Discovered session: " << message << " (From: " << sender_endpoint.address() << ")\n";
	}
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
