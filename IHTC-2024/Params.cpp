#include "Params.h"

void to_json(nlohmann::json& j, const Params& data)
{
    j = nlohmann::json
    {
        {"hardRestrictionWeight", data.hardRestrictionWeight},
        {"maxIteration", data.maxIteration},
        {"mutationProbability", data.mutationProbability},
        {"neighbourNumber", data.neighbourNumber},
        {"prizeSize", data.prizeSize},
        {"increaseTempIters", data.increaseTempIters},
        {"genderGrouperIter", data.genderGrouperIter},
        {"simplexCoolingMultiplier", data.simplexCoolingMultiplier},
        {"solverRepetitionAmount", data.solverRepetitionAmount},
        {"startingTemperature", data.startingTemperature},
        {"stopTemperature", data.stopTemperature},
        {"initSolver", solverTypeToJson(data.initSolver)},
        {"outputSolver", solverTypeToJson(data.outputSolver)},
        {"neighbourGenerator", neighbourGeneratorTypeToJson(data.neighbourGenerator)},
        {"outputPath", data.outputPath}
    };
}

void from_json(const nlohmann::json& j, Params& data)
{
    data.hardRestrictionWeight = j.at("hardRestrictionWeight").get<double>();
    data.maxIteration = j.at("maxIteration").get<int>();
    data.mutationProbability = j.at("mutationProbability").get<double>();
    data.neighbourNumber = j.at("neighbourNumber").get<int>();
    data.prizeSize = j.at("prizeSize").get<int>();
    data.increaseTempIters = j.at("increaseTempIters").get<int>();
    data.genderGrouperIter = j.at("genderGrouperIter").get<int>();
    data.simplexCoolingMultiplier = j.at("simplexCoolingMultiplier").get<double>();
    data.solverRepetitionAmount = j.at("solverRepetitionAmount").get<int>();
    data.startingTemperature = j.at("startingTemperature").get<double>();
    data.stopTemperature = j.at("stopTemperature").get<double>();
    data.initSolver = solverTypeFromJson(j.at("initSolver").get<std::string>());
    data.outputSolver = solverTypeFromJson(j.at("outputSolver").get<std::string>());
    data.neighbourGenerator = neighbourGeneratorTypeFromJson(j.at("neighbourGenerator").get<std::string>());
    data.outputPath = j.at("outputPath").get<std::string>();
}
