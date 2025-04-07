#include "AllGameParameters.h"

std::string& AllGameParameters::name()
{
    return _name;
}

bool AllGameParameters::isPlayerOpponent()
{
    return _isPlayerOpponent;
}

int AllGameParameters::gameTime()
{
    return _gameTime;
}

GameLevel AllGameParameters::gameLevel()
{
    return _gameLevel;
}

GameWinningMode AllGameParameters::winningMode()
{
    return _winningMode;
}

int AllGameParameters::maxIteration()
{
    return _maxIteration;
}

int AllGameParameters::genderGroupIter()
{
    return _genderGroupIter;
}

int AllGameParameters::neighbourSize()
{
    return _neighbourSize;
}

NeighbourGeneratorValues AllGameParameters::neighbourGenerator()
{
    return _neighbourGenerator;
}

int AllGameParameters::increaseTempIters()
{
    return _increaseTempIters;
}

InitSolverValue AllGameParameters::initSolver()
{
    return _initSolver;
}

int AllGameParameters::startingTemperature()
{
    return _startingTemperature;
}

int AllGameParameters::stopTemperature()
{
    return _stopTemperature;
}

int AllGameParameters::prizeSize()
{
    return _prizeSize;
}

int AllGameParameters::coolingMultiplier()
{
    return _coolingMultiplier;
}

void AllGameParameters::setName(const std::string& name)
{
    _name = name;
}

void AllGameParameters::setIsPlayerOpponent(bool isPlayerOpponent)
{
    _isPlayerOpponent = isPlayerOpponent;
}

void AllGameParameters::setGameTime(int gameTime)
{
    _gameTime = gameTime;
}

void AllGameParameters::setGameLevel(GameLevel gameLevel)
{
    _gameLevel = gameLevel;
}

void AllGameParameters::setWinningMode(GameWinningMode winningMode)
{
    _winningMode = winningMode;
}

void AllGameParameters::setMaxIteration(int maxIteration)
{
    _maxIteration = maxIteration;
}

void AllGameParameters::setGenderGroupIter(int genderGroupIter)
{
    _genderGroupIter = genderGroupIter;
}

void AllGameParameters::setNeighbourSize(int neighbourSize)
{
    _neighbourSize = neighbourSize;
}

void AllGameParameters::setNeighbourGenerator(NeighbourGeneratorValues neighbourGenerator)
{
    _neighbourGenerator = neighbourGenerator;
}

void AllGameParameters::setIncreaseTempIters(int increaseTempIters)
{
    _increaseTempIters = increaseTempIters;
}

void AllGameParameters::setInitSolver(InitSolverValue initSolver)
{
    _initSolver = initSolver;
}

void AllGameParameters::setStartingTemperature(int startingTemperature)
{
    _startingTemperature = startingTemperature;
}

void AllGameParameters::setStopTemperature(int stopTemperature)
{
    _stopTemperature = stopTemperature;
}

void AllGameParameters::setPrizeSize(int prizeSize)
{
    _prizeSize = prizeSize;
}

void AllGameParameters::setCoolingMultiplier(int coolingMulitplier)
{
    _coolingMultiplier = coolingMulitplier;
}
