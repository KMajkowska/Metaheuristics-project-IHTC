#pragma once

#include <string>

#include <WinnerJudgeType.h>
#include <GameLevel.h>
#include <NeighbourGeneratorType.h>
#include <SolverType.h>

class AllGameParameters
{
public:
    AllGameParameters() = default;
    AllGameParameters(const AllGameParameters& other) = default;
    ~AllGameParameters() = default;

//getters
    std::string name() const;
    int gameTime() const;
    GameLevel gameLevel() const;
    WinnerJudgeType judgeType() const;
    int maxIteration() const;
    int genderGroupIter() const;
    int neighbourSize() const;
    NeighbourGeneratorType neighbourGenerator() const;
    int increaseTempIters() const;
    SolverType initSolver() const;
    int startingTemperature() const;
    int stopTemperature() const;
    int prizeSize() const;
    double coolingMultiplier() const;
    int roundNumber() const;
    GameLevel inputParametersLevel() const;

//setters
    void setName(const std::string& name);
    void setGameTime(int gameTime);
    void setGameLevel(GameLevel gameLevel);
    void setJudgeType(WinnerJudgeType winningMode);
    void setMaxIteration(int maxIteration);
    void setGenderGroupIter(int genderGroupIter);
    void setNeighbourSize(int neighbourSize);
    void setNeighbourGenerator(NeighbourGeneratorType neighbourGenerator);
    void setIncreaseTempIters(int increaseTempIters);
    void setInitSolver(SolverType initSolver);
    void setStartingTemperature(int startingTemperature);
    void setStopTemperature(int stopTemperature);
    void setPrizeSize(int prizeSize);
    void setCoolingMultiplier(double coolingMulitplier);
    void setRoundNumber(int roundNumber);
    void setInputParametersLevel(GameLevel inputParametersLevel);

private:
    std::string _name;
	int _gameTime;
	GameLevel _gameLevel;
    WinnerJudgeType _judgeType;
	int _maxIteration;
    int _neighbourSize;
    int _genderGroupIter;
    NeighbourGeneratorType _neighbourGenerator;
    int _increaseTempIters;
    SolverType _initSolver;
    int _startingTemperature;
    int _stopTemperature;
    int _prizeSize;
    double _coolingMultiplier;
    int _roundNumber;
    GameLevel _inputParametersLevel;
};