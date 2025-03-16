#include "solverUtils.h"
#include "NeighbourGeneratorQueue.h"
#include "NeighbourGeneratorPrizeBest.h"
#include "NeighbourGeneratorTop.h"
#include "NeighbourGeneratorTournament.h"


//std::unique_ptr<IHTCSolver> getSolver(
//	SolverType solverType,
//	ICIndividualConsumer& consumer,
//	const Params& params,
//	const ProblemData& problemData
//)
//{
//	switch (solverType)
//	{
//	case SolverType::SA:
//		return std::make_unique<SASolver>(
//			problemData,
//			params.startingTemperature(),
//			TemperatureOperator(coolingScheme, params.increaseTempIters()),
//			RANDOM_GENERATOR,
//			stopCriterium,
//			params.neighbourNumber(),
//			*generator,
//			consumer,
//			GenderGrouper(params.genderGrouperIter(), problemData, RANDOM_GENERATOR),
//			IHTCMutatorNurseRoomCover(RANDOM_GENERATOR, problemData, params.mutationProbability())
//		);
//	case SolverType::RAND:
//		return std::make_unique<RandomSolver>(problemData, RANDOM_GENERATOR, consumer);
//	case SolverType::GREEDY:
//		return std::make_unique<GreedySolver>(problemData, RANDOM_GENERATOR, consumer);
//	default:
//		throw std::invalid_argument("Incorrect solver type");
//	}
//
//}

std::unique_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
)
{
	switch (params.neighbourGenerator())
	{
		case NeighbourGeneratorType::QUEUE:
			return std::make_unique<NeighbourGeneratorQueue>(mutators, problem);
		case NeighbourGeneratorType::PRIZE_BEST:
			return std::make_unique<NeighbourGeneratorPrizeBest>(mutators, problem, params.prizeSize());
		case NeighbourGeneratorType::TOP:
			return std::make_unique<NeighbourGeneratorTop>(mutators, problem);
		case NeighbourGeneratorType::TOURNAMENT:
			return std::make_unique<NeighbourGeneratorTournament>(mutators, problem);
		default:
			throw std::invalid_argument("Incorrect neighbour generator");
	}
}
