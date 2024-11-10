#include "IHTCProblemIO.h"

ProblemData IHTCProblemIO::parseFromJSON(const std::string& problemFilepath)
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

SolutionData IHTCProblemIO::parseFromJSONSolution(const std::string& problemFilepath)
{
    std::ifstream inputFile(problemFilepath);

    if (!inputFile) {
        inputFile.close();

        throw std::invalid_argument("JSON solution file cannot be opened");
    }

    nlohmann::json jsonData;
    inputFile >> jsonData;

    SolutionData solution;
    nlohmann::from_json(jsonData, solution);

    return solution;
}


SolutionData IHTCProblemIO::parseToSolution(const CIndividual& individual, const ProblemData& problemData)
{
    SolutionData solutionData;

    const auto solutionPatients = individual.getPatients();

    solutionData.setPatients(solutionPatients);

    const auto& nurses = problemData.getNurses();
    const auto& solutionAssignments = individual.getAssignments();
    std::vector<NurseOutputDTO> outputNurses;
    outputNurses.reserve((solutionAssignments.size()));

    if (nurses.size() != solutionAssignments.size())
    {
        throw std::invalid_argument("Representation of nurses is incorrect, something went wrong");
    }

    std::size_t counter = 0;
    for (const auto& nurse : nurses)
    {
        const auto& assignments = solutionAssignments.at(nurse.getId());

        outputNurses.push_back(NurseOutputDTO(nurse.getId(), assignments));

        ++counter;
    }

    solutionData.setNurses(outputNurses);

    return solutionData;
}

std::string IHTCProblemIO::parseSolutionToJSON(const SolutionData& solution)
{
    nlohmann::json jsonObject = solution;

    return jsonObject.dump(JSON_INDENT);
}
