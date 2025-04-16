#include "AllGameParameters.h"

std::string AllGameParameters::name() const
{
    return _name;
}

bool AllGameParameters::isPlayerOpponent() const
{
    return _isPlayerOpponent;
}

int AllGameParameters::gameTime() const
{
    return _gameTime;
}

GameLevel AllGameParameters::gameLevel() const
{
    return _gameLevel;
}

WinnerJudgeType AllGameParameters::judgeType() const
{
    return _judgeType;
}

int AllGameParameters::maxIteration() const
{
    return _maxIteration;
}

int AllGameParameters::genderGroupIter() const
{
    return _genderGroupIter;
}

int AllGameParameters::neighbourSize() const
{
    return _neighbourSize;
}

NeighbourGeneratorType AllGameParameters::neighbourGenerator() const
{
    return _neighbourGenerator;
}

int AllGameParameters::increaseTempIters() const
{
    return _increaseTempIters;
}

SolverType AllGameParameters::initSolver() const
{
    return _initSolver;
}

int AllGameParameters::startingTemperature() const
{
    return _startingTemperature;
}

int AllGameParameters::stopTemperature() const
{
    return _stopTemperature;
}

int AllGameParameters::prizeSize() const
{
    return _prizeSize;
}

int AllGameParameters::coolingMultiplier() const
{
    return _coolingMultiplier;
}

int AllGameParameters::roundNumber() const
{
    return _roundNumber;
}

GameLevel AllGameParameters::inputParametersLevel() const
{
    return _inputParametersLevel;
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

void AllGameParameters::setJudgeType(WinnerJudgeType judgeType)
{
    _judgeType = judgeType;
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

void AllGameParameters::setNeighbourGenerator(NeighbourGeneratorType neighbourGenerator)
{
    _neighbourGenerator = neighbourGenerator;
}

void AllGameParameters::setIncreaseTempIters(int increaseTempIters)
{
    _increaseTempIters = increaseTempIters;
}

void AllGameParameters::setInitSolver(SolverType initSolver)
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

void AllGameParameters::setRoundNumber(int roundNumber)
{
    _roundNumber = roundNumber;
}

void AllGameParameters::setInputParametersLevel(GameLevel inputParametersLevel)
{
    _inputParametersLevel = inputParametersLevel;
}
