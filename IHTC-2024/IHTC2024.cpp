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
#include "SASolverBuilder.h"
#include "GreedySolverBuilder.h"
#include <QtWidgets/qapplication.h>
#include "MainWindow.h"
#include <welcomeScreen.h>
#include <QStackedWidget>


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
	IHTCProblem problem(problemData, getViolatedFromSolution, fitnessCalculator);

	auto initSolver { GreedySolverBuilder(params, problemData, randomGenerator, logger).build() };
	auto currentSolver { SASolverBuilder(params, problemData, randomGenerator, logger, problem).build() };

	evaluateProblem(params.solverRepetitionAmount(), problem, currentSolver, initSolver);
}

void broadcastSession(short port) 
{
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
	socket.set_option(boost::asio::socket_base::broadcast(true));

	boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), port);

	while (true) 
	{
		std::string message = "TicTacToeSession: 192.168.1.100:12345"; // Replace with actual IP
		socket.send_to(boost::asio::buffer(message), broadcast_endpoint);
		std::cout << "Broadcasting game session...\n";
		std::this_thread::sleep_for(std::chrono::seconds(2)); // Broadcast every 2 seconds
	}
}

void discoverSessions(short port) 
{
	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));

	char buffer[1024];
	boost::asio::ip::udp::endpoint sender_endpoint;

	std::cout << "Listening for game sessions...\n";
	while (true) 
	{
		size_t length = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
		std::string message(buffer, length);
		std::cout << "Discovered session: " << message << " (From: " << sender_endpoint.address() << ")\n";
	}
}

int main(int argc, char* argv[]) {
	try {
		QApplication app(argc, argv);

		MainWindow mainWindow;
		mainWindow.resize(1100, 800);
		mainWindow.show();

		run(argc, argv);

		return app.exec();

	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1; 
	}
}
