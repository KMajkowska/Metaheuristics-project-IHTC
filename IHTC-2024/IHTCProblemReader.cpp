#include "IHTCProblemReader.h"

ProblemData IHTCProblemReader::parseFromJSON(const std::string& problemFilepath)
{
    std::ifstream inputFile(problemFilepath);

    if (!inputFile) {
        inputFile.close();

        throw std::invalid_argument("JSON problem file cannot be opened");
    }

    nlohmann::json jsonData;
    inputFile >> jsonData;

    ProblemData problem;
    nlohmann::from_json(jsonData, problem);

    return problem;
}
