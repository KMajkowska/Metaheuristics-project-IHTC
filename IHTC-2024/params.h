#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "SolverType.h"
#include "NeighbourGeneratorType.h"
#include "CoolingSchemeType.h"
#include "enumOperations.h"

static const std::string DEFAULT_PROBLEM_FILE = "../datasets/ihtc2024_test_dataset/test01.json";
static const std::string DEFAULT_PARAMS_FILE = "./params.json";

class Params
{
public:
	Params() = default;
	Params(const Params& other) = default;
	Params(Params&& other) = default;

    void setOutputPath(const std::string& path);
    void setHardRestrictionWeight(double weight);
    void setMutationProbability(double probability);
    void setNeighbourNumber(int number);
    void setMaxIteration(int iteration);
    void setPrizeSize(int size);
    void setIncreaseTempIters(int iters);
    void setGenderGrouperIter(int iters);
    void setStartingTemperature(double temperature);
    void setStopTemperature(double temperature);
    void setSimplexCoolingMultiplier(double multiplier);
    void setSolverRepetitionAmount(int amount);
    void setInitSolver(SolverType solver);
    void setOutputSolver(SolverType solver);
    void setNeighbourGenerator(NeighbourGeneratorType generator);
    void setCoolingSchemeType(CoolingSchemeType coolingSchemeType);

    const std::string& outputPath() const;
    double hardRestrictionWeight() const;
    double mutationProbability() const;
    int neighbourNumber() const;
    int maxIteration() const;
    int prizeSize() const;
    int increaseTempIters() const;
    int genderGrouperIter() const;
    double startingTemperature() const;
    double stopTemperature() const;
    double simplexCoolingMultiplier() const;
    int solverRepetitionAmount() const;
    SolverType initSolver() const;
    SolverType outputSolver() const;
    NeighbourGeneratorType neighbourGenerator() const;
    CoolingSchemeType coolingSchemeType() const;

private:
    std::string _outputPath { "./" };
    double _hardRestrictionWeight { 0.0 };
    double _mutationProbability { 0.0 };
    int _neighbourNumber { 0 };
    int _maxIteration { 0 };
    int _prizeSize { 0 };
    int _increaseTempIters { 0 };
    int _genderGrouperIter { 0 };
    double _startingTemperature { 0.0 };
    double _stopTemperature { 0.0 };
    double _simplexCoolingMultiplier { 0.0 };
    int _solverRepetitionAmount { 0 };
    SolverType _initSolver { SolverType::UNKNOWN };
    SolverType _outputSolver { SolverType::UNKNOWN };
    NeighbourGeneratorType _neighbourGenerator { NeighbourGeneratorType::UNKNOWN };
    CoolingSchemeType _coolingSchemeType { CoolingSchemeType:: UNKNOWN };
};

void to_json(nlohmann::json& j, const Params& data);
void from_json(const nlohmann::json& j, Params& data);