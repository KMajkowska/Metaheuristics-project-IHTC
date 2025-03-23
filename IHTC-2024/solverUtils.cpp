#include "solverUtils.h"


std::vector<std::shared_ptr<IMutator>> getMutators(const ProblemData& problemData, std::mt19937& randGenerator, const Params& params)
{
	std::vector<std::shared_ptr<IMutator>> mutators =
	{
		std::make_shared<IHTCMutatorRoom>(randGenerator, problemData, params.mutationProbability()),
		std::make_shared<IHTCMutatorDay>(randGenerator, problemData, params.mutationProbability()),
		std::make_shared<IHTCMutatorAssignment>(randGenerator, problemData, params.mutationProbability()),
	};

	if (problemData.operatingTheaters().size() > 1 && problemData.patients().size() > 1)
	{
		mutators.push_back(
			std::make_shared<IHTCMutatorOT>(randGenerator, problemData, params.mutationProbability())
		);
	}

	return mutators;
}

std::shared_ptr<IStopCriterium> getStopCriterium(const Params& params)
{
	switch (params.stopCriteriumType())
	{
	case StopCriteriumType::TEMPERATURE:
		return std::make_shared<StopCriteriumTemperature>(params.stopTemperature());
	case StopCriteriumType::ITERATION:
		return std::make_shared<StopCriteriumIter>(params.maxIteration());
	case StopCriteriumType::TIME:
		return std::make_shared<StopCriteriumTime>(params.stopMillis());
	default:
		throw std::invalid_argument("Incorrect stop criterium");
	}
}

std::shared_ptr<ICoolingScheme> getCoolingScheme(const Params& params)
{
	switch (params.coolingSchemeType())
	{
	case CoolingSchemeType::GEMAN_AND_GEMAN:
		return std::make_shared<GemanAndGemanCoolingScheme>();
	case CoolingSchemeType::SIMPLEX:
		return std::make_shared<SimplexCoolingScheme>(params.simplexCoolingMultiplier());
	case CoolingSchemeType::VARIABLE:
		return std::make_shared<VariableCoolingScheme>(params.maxIteration());
	default:
		throw std::invalid_argument("Incorrect cooling scheme");
	}
}

std::shared_ptr<INeighbourGenerator> getNeighbourGenerator(
	const std::vector<std::shared_ptr<IMutator>> mutators,
	const Params& params,
	const IProblem& problem
)
{
	switch (params.neighbourGenerator())
	{
		case NeighbourGeneratorType::QUEUE:
			return std::make_shared<NeighbourGeneratorQueue>(mutators, problem);
		case NeighbourGeneratorType::PRIZE_BEST:
			return std::make_shared<NeighbourGeneratorPrizeBest>(mutators, problem, params.prizeSize());
		case NeighbourGeneratorType::TOP:
			return std::make_shared<NeighbourGeneratorTop>(mutators, problem);
		case NeighbourGeneratorType::TOURNAMENT:
			return std::make_shared<NeighbourGeneratorTournament>(mutators, problem);
		default:
			throw std::invalid_argument("Incorrect neighbour generator");
	}
}