#include "CSolutionHandler.h"

void CSolutionHandler::setCurrentLocal(SolutionData solution)
{
	_currentLocal = std::move(solution);
}

void CSolutionHandler::setCurrentOpponent(SolutionData solution)
{
	_currentOpponent = std::move(solution);
}

void CSolutionHandler::setBestLocal(SolutionData solution)
{
	_bestLocal = std::move(solution);
}

void CSolutionHandler::setBestOpponent(SolutionData solution)
{
	_bestOpponent = std::move(solution);
}

SolutionData& CSolutionHandler::currentLocal()
{
	return _currentLocal;
}

SolutionData& CSolutionHandler::currentOpponent()
{
	return _currentOpponent;
}

SolutionData& CSolutionHandler::bestLocal()
{
	return _bestLocal;
}

SolutionData& CSolutionHandler::bestOpponent()
{
	return _bestOpponent;
}

void CSolutionHandler::consumeLocal(SolutionData solution)
{
	_currentLocal = solution;

	if (_currentLocal.fitness() < _bestLocal.fitness())
	{
		_bestLocal = _currentLocal;
	}
}

void CSolutionHandler::consumeOpponent(SolutionData solution)
{
	_currentOpponent = solution;

	if (_currentOpponent.fitness() < _bestOpponent.fitness())
	{
		_bestOpponent = _currentOpponent;
	}
}
