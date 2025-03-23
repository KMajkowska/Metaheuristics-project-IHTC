#include "CGameNetwork.h"
#include "CIndividualObservable.h"
#include "FitnessCalculator.h"
#include "IHTCProblem.h"
#include "solverBuilderUtils.h"


CGameNetwork::CGameNetwork(
	std::shared_ptr<INetworkExchanger> exchanger,
	std::shared_ptr<CPlayer> localPlayer,
	std::shared_ptr<CPlayer> opponentPlayer,
	std::shared_ptr<IWinnerJudge> judge,
	const ProblemData& problemData,
	const Params& params
) :
	ICGame(localPlayer, opponentPlayer, judge, problemData, params),
	_exchanger(exchanger)
{}

CSolutionHandler CGameNetwork::startRound()
{
	CSolutionDataHandlerNetwork handler(_exchanger);

	CIndividualObservable consumer(_problemData);

	consumer.addObserver([&handler](SolutionData localSolution)
		{
			handler.consumeLocal(localSolution);
		});

	IHTCProblem problem(_problemData, getViolatedFromSolution, FitnessCalculator(_localParams.hardRestrictionWeight()));

	auto localInitSolver = getSolverBuilder(_localParams.initSolver(), _localParams, _problemData, consumer, problem)->build();
	auto localOutputSolver = getSolverBuilder(_localParams.outputSolver(), _localParams, _problemData, consumer, problem)->build();

	std::future<CIndividual> localFuture = std::async(std::launch::async, [&]()
		{
			return localOutputSolver->solve(problem, localInitSolver->solve(problem, CIndividual()));
		});

	CIndividual localIndividual{ localFuture.get() };

	return handler;
}
