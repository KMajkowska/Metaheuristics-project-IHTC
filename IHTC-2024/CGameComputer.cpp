#include "CGameComputer.h"

CGameComputer::CGameComputer(
	std::shared_ptr<CPlayer> localPlayer,
	std::shared_ptr<CPlayer> opponentPlayer,
	std::shared_ptr<IWinnerJudge> judge,
	const ProblemData problemData,
	const Params params
) :
	ICGame(localPlayer, opponentPlayer, judge, problemData, params)
{}

CSolutionHandler CGameComputer::startRound()
{
	CSolutionHandler handler;

	CIndividualObservable consumerLocal(_problemData);
	CIndividualObservable consumerOpponent(_problemData);

	consumerLocal.addObserver([&handler](SolutionData localSolution)
		{
			handler.consumeLocal(localSolution);
		});

	consumerOpponent.addObserver([&handler](SolutionData localSolution)
		{
			handler.consumeOpponent(localSolution);
		});

	FitnessCalculator fitnessCalculator(_localParams.hardRestrictionWeight());
	IHTCProblem problem(_problemData, getViolatedFromSolution, fitnessCalculator);

	std::future<CIndividual> localFuture = std::async(std::launch::async, [&]()
		{
			auto localInitSolver{ getSolverBuilder(_localParams.initSolver(), _localParams, _problemData, consumerLocal, problem)->build() };
			auto localOutputSolver{ getSolverBuilder(_localParams.outputSolver(), _localParams, _problemData, consumerLocal, problem)->build() };

			CIndividual localStartingIndividual;
			auto initialized{ localInitSolver->solve(problem, localStartingIndividual) };

			return localOutputSolver->solve(problem, initialized);
		});

	// TODO: make the opponent create params
	std::future<CIndividual> opponentFuture = std::async(std::launch::async, [&]()
		{
			auto opponentInitSolver = getSolverBuilder(_localParams.initSolver(), _localParams, _problemData, consumerOpponent, problem)->build();
			auto opponentOutputSolver = getSolverBuilder(_localParams.outputSolver(), _localParams, _problemData, consumerOpponent, problem)->build();
			
			CIndividual opponentStartingIndividual;
			auto initialized{ opponentInitSolver->solve(problem, opponentStartingIndividual) };

			return opponentOutputSolver->solve(problem, initialized);
		});

	CIndividual localIndividual { localFuture.get() };
	CIndividual opponentIndividual { opponentFuture.get() };

	return handler;
}