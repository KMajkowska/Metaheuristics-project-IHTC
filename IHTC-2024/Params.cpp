#include "Params.h"

const std::string& Params::outputPath() const 
{
    return _outputPath; 
}

double Params::hardRestrictionWeight() const 
{
    return _hardRestrictionWeight;
}

double Params::mutationProbability() const
{ 
    return _mutationProbability;
}

int Params::neighbourNumber() const
{
    return _neighbourNumber; 
}

int Params::maxIteration() const 
{
    return _maxIteration; 
}

int Params::prizeSize() const 
{ 
    return _prizeSize; 
}

int Params::increaseTempIters() const 
{
    return _increaseTempIters;
}

int Params::genderGrouperIter() const
{
    return _genderGrouperIter;
}

double Params::startingTemperature() const 
{
    return _startingTemperature;
}

double Params::stopTemperature() const 
{
    return _stopTemperature; 
}

double Params::simplexCoolingMultiplier() const 
{
    return _simplexCoolingMultiplier;
}

int Params::solverRepetitionAmount() const 
{
    return _solverRepetitionAmount;
}

int Params::stopMillis() const
{
    return _stopMillis;
}

SolverType Params::initSolver() const 
{
    return _initSolver; 
}

SolverType Params::outputSolver() const 
{
    return _outputSolver;
}

NeighbourGeneratorType Params::neighbourGenerator() const
{
    return _neighbourGenerator;
}

CoolingSchemeType Params::coolingSchemeType() const
{
    return _coolingSchemeType;
}

StopCriteriumType Params::stopCriteriumType() const
{
    return _stopCriteriumType;
}

void Params::setOutputPath(const std::string& path) 
{
    _outputPath = path;
}

void Params::setHardRestrictionWeight(double weight) 
{
    _hardRestrictionWeight = weight;
}

void Params::setMutationProbability(double probability) 
{
    _mutationProbability = probability;
}

void Params::setNeighbourNumber(int number) 
{
    _neighbourNumber = number;
}

void Params::setMaxIteration(int iteration)
{
    _maxIteration = iteration; 
}

void Params::setPrizeSize(int size) 
{
    _prizeSize = size; 
}

void Params::setIncreaseTempIters(int iters)
{
    _increaseTempIters = iters; 
}

void Params::setGenderGrouperIter(int iters) 
{
    _genderGrouperIter = iters; 
}

void Params::setStartingTemperature(double temperature)
{
    _startingTemperature = temperature; 
}

void Params::setStopTemperature(double temperature) 
{
    _stopTemperature = temperature; 
}

void Params::setSimplexCoolingMultiplier(double multiplier) 
{
    _simplexCoolingMultiplier = multiplier; 
}

void Params::setSolverRepetitionAmount(int amount) 
{
    _solverRepetitionAmount = amount; 
}

void Params::setStopMillis(int millis)
{
    _stopMillis = millis;
}

void Params::setInitSolver(SolverType solver) 
{
    _initSolver = solver; 
}

void Params::setOutputSolver(SolverType solver) 
{
    _outputSolver = solver; 
}

void Params::setNeighbourGenerator(NeighbourGeneratorType generator)
{
    _neighbourGenerator = generator;
}

void Params::setCoolingSchemeType(CoolingSchemeType coolingSchemeType)
{
    _coolingSchemeType = coolingSchemeType;
}

void Params::setStopCriteriumType(StopCriteriumType stopCriteriumType)
{
    _stopCriteriumType = stopCriteriumType;
}

void to_json(nlohmann::json& j, const Params& data)
{
    j = nlohmann::json
    {
        {"hardRestrictionWeight", data.hardRestrictionWeight()},
        {"maxIteration", data.maxIteration()},
        {"mutationProbability", data.mutationProbability()},
        {"neighbourNumber", data.neighbourNumber()},
        {"prizeSize", data.prizeSize()},
        {"increaseTempIters", data.increaseTempIters()},
        {"genderGrouperIter", data.genderGrouperIter()},
        {"simplexCoolingMultiplier", data.simplexCoolingMultiplier()},
        {"solverRepetitionAmount", data.solverRepetitionAmount()},
        {"startingTemperature", data.startingTemperature()},
        {"stopTemperature", data.stopTemperature()},
        {"stopMillis", data.stopMillis()},
        {"initSolver", enumToString<SolverType>(data.initSolver())},
        {"outputSolver", enumToString<SolverType>(data.outputSolver())},
        {"neighbourGenerator", enumToString<NeighbourGeneratorType>(data.neighbourGenerator())},
        {"outputPath", data.outputPath()},
        {"coolingSchemeType", enumToString<CoolingSchemeType>(data.coolingSchemeType())},
        {"stopCriteriumType", enumToString<StopCriteriumType>(data.stopCriteriumType())},
    };
}

void from_json(const nlohmann::json& j, Params& data)
{
    data.setHardRestrictionWeight(j.at("hardRestrictionWeight").get<double>());
    data.setMaxIteration(j.at("maxIteration").get<int>());
    data.setMutationProbability(j.at("mutationProbability").get<double>());
    data.setNeighbourNumber(j.at("neighbourNumber").get<int>());
    data.setPrizeSize(j.at("prizeSize").get<int>());
    data.setIncreaseTempIters(j.at("increaseTempIters").get<int>());
    data.setGenderGrouperIter(j.at("genderGrouperIter").get<int>());
    data.setSimplexCoolingMultiplier(j.at("simplexCoolingMultiplier").get<double>());
    data.setSolverRepetitionAmount(j.at("solverRepetitionAmount").get<int>());
    data.setStartingTemperature(j.at("startingTemperature").get<double>());
    data.setStopTemperature(j.at("stopTemperature").get<double>());
    data.setStopMillis(j.at("stopMillis").get<int>());
    data.setInitSolver(stringToEnum<SolverType>(j.at("initSolver").get<std::string>()));
    data.setOutputSolver(stringToEnum<SolverType>(j.at("outputSolver").get<std::string>()));
    data.setNeighbourGenerator(stringToEnum<NeighbourGeneratorType>(j.at("neighbourGenerator").get<std::string>()));
    data.setOutputPath(j.at("outputPath").get<std::string>());
    data.setCoolingSchemeType(stringToEnum<CoolingSchemeType>(j.at("coolingSchemeType").get<std::string>()));
    data.setStopCriteriumType(stringToEnum<StopCriteriumType>(j.at("stopCriteriumType").get<std::string>()));
}
