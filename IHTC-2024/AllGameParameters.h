#pragma once

#include "GameLevel.h"
#include "GameTimeValues.h"
#include "GameWinningMode.h"
#include <NeighbourGeneratorValues.h>
#include "InitSolverValue.h"

class AllGameParameters
{
public:
    AllGameParameters() = default;

//getters
    std::string& name();
    bool isPlayerOpponent();
    int gameTime();
    GameLevel gameLevel();
    GameWinningMode winningMode();
    int maxIteration();
    int genderGroupIter();
    int neighbourSize();
    NeighbourGeneratorValues neighbourGenerator();
    int increaseTempIters();
    InitSolverValue initSolver();
    int startingTemperature();
    int stopTemperature();
    int prizeSize();
    int coolingMultiplier();

//setters
    void setName(const std::string& name);
    void setIsPlayerOpponent(bool isPlayerOpponent);
    void setGameTime(int gameTime);
    void setGameLevel(GameLevel gameLevel);
    void setWinningMode(GameWinningMode winningMode);
    void setMaxIteration(int maxIteration);
    void setGenderGroupIter(int genderGroupIter);
    void setNeighbourSize(int neighbourSize);
    void setNeighbourGenerator(NeighbourGeneratorValues neighbourGenerator);
    void setIncreaseTempIters(int increaseTempIters);
    void setInitSolver(InitSolverValue initSolver);
    void setStartingTemperature(int startingTemperature);
    void setStopTemperature(int stopTemperature);
    void setPrizeSize(int prizeSize);
    void setCoolingMultiplier(int coolingMulitplier);

private:
    std::string _name;
	bool _isPlayerOpponent;
	int _gameTime;
	GameLevel _gameLevel;
	GameWinningMode _winningMode;
	int _maxIteration;
    int _neighbourSize;
    int _genderGroupIter;
    NeighbourGeneratorValues _neighbourGenerator;
    int _increaseTempIters;
    InitSolverValue _initSolver;
    int _startingTemperature;
    int _stopTemperature;
    int _prizeSize;
    int _coolingMultiplier;
};