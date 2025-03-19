#include "SASolverBuilder.h"

SASolverBuilder::SASolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer, const IProblem& problem) :
	IHTCSolverBuilder(params, problemData, randGenerator, consumer),
	_problem(problem)
{}

std::optional<SASolver> SASolverBuilder::prepareForBuild() const
{

	return SASolver(
		_problemData,
		_params.startingTemperature(),
		std::make_shared<TemperatureOperator>(getCoolingScheme(_params), _params.increaseTempIters()),
		_randGenerator,
		getStopCriterium(_params),
		_params.neighbourNumber(),
		getNeighbourGenerator(getMutators(_problemData, _randGenerator, _params), _params, _problem),
		_consumer,
		std::move(GenderGrouper(_params.genderGrouperIter(), _problemData, _randGenerator)),
		std::move(IHTCMutatorNurseRoomCover(_randGenerator, _problemData, _params.mutationProbability()))
	);
}
