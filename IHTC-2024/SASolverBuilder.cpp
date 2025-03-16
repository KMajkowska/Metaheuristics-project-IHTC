#include "SASolverBuilder.h"

SASolverBuilder::SASolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer, const IProblem& problem) :
	IHTCSolverBuilder(params, problemData, randGenerator, consumer),
	_problem(problem)
{}

std::optional<SASolver> SASolverBuilder::prepareForBuild() const
{

	auto tempOperator = std::make_shared<TemperatureOperator>(*getCoolingScheme(_params), _params.increaseTempIters());

	return SASolver(
		_problemData,
		_params.startingTemperature(),
		*tempOperator,
		_randGenerator,
		*getStopCriterium(_params),
		_params.neighbourNumber(),
		*getNeighbourGenerator(getMutators(_problemData, _randGenerator, _params), _params, _problem),
		_consumer,
		GenderGrouper(_params.genderGrouperIter(), _problemData, _randGenerator),
		IHTCMutatorNurseRoomCover(_randGenerator, _problemData, _params.mutationProbability())
	);
}
