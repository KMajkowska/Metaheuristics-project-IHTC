#include "CGameNetwork.h"

CGameNetwork::CGameNetwork(
	std::shared_ptr<INetworkExchanger> exchanger,
	std::shared_ptr<CPlayer> localPlayer,
	std::shared_ptr<CPlayer> opponentPlayer,
	std::shared_ptr<IWinnerJudge> judge,
	const ProblemData problemData,
	const Params params
) :
	ICGame(localPlayer, opponentPlayer, judge, problemData, params),
	_exchanger(exchanger)
{}

CSolutionHandler CGameNetwork::startRound()
{
	std::promise<void> endTransmission;
	std::future<void> endFuture = endTransmission.get_future();

	_exchanger->setOnEndTransmission([&endTransmission]()
		{
			endTransmission.set_value();
		});

	CSolutionDataHandlerNetwork handler(_exchanger);

	CIndividualObservable consumer(_problemData);

	consumer.addObserver([&handler, this](SolutionData localSolution)
		{
			handler.consumeLocal(localSolution);

			if (_onLocal)
			{
				_onLocal(localSolution);
			}
		});

	_exchanger->addObserver([&handler, this](std::string solution)
		{
			auto parsed{ nlohmann::json::parse(solution) };
			auto solutionDataOpt{ jsonToObject<SolutionData>(parsed) };

			if (solutionDataOpt)
			{
				handler.consumeOpponent(solutionDataOpt.value());

				if (_onOpponent)
				{
					_onOpponent(solutionDataOpt.value());
				}
			}

		});

	IHTCProblem problem(_problemData, getViolatedFromSolution, FitnessCalculator(_localParams.hardRestrictionWeight()));

	auto localInitSolver = getSolverBuilder(_localParams.initSolver(), _localParams, _problemData, consumer, problem)->build();
	auto localOutputSolver = getSolverBuilder(_localParams.outputSolver(), _localParams, _problemData, consumer, problem)->build();

	localOutputSolver->solve(problem, localInitSolver->solve(problem, CIndividual()));

	_exchanger->tellEndOfTransmission();

	endFuture.wait();

	_exchanger->removeObservers();

	return handler;
}
