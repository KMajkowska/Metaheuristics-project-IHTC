#include "IHTCProblemIO.h"

ProblemData IHTCProblemIO::parseFromJSON(const std::string& problemFilepath) const
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

SolutionData IHTCProblemIO::parseToSolution(const CIndividual& individual, const ProblemData& problemData) const
{
    SolutionData solutionData;

    const std::vector<IncomingPatientDTO>& patients = problemData.getPatients();
    const auto& solutionPatients = individual.getPatients();
    std::vector<std::string> patientIds;
    patientIds.reserve((patients.size()));

    for (const auto& patient : patients)
    {
        patientIds.push_back(patient.getId());
    }

    if (patientIds.size() != solutionPatients.size())
    {
        throw std::invalid_argument("Representation of population is incorrect, something went wrong");
    }

    std::vector<PatientOutputDTO> outputPatients;
    outputPatients.reserve(patientIds.size());

    std::size_t counter = 0;
    for (const auto& patientId : patientIds)
    {
        const auto& patient = solutionPatients[counter];

        outputPatients.push_back(PatientOutputDTO(patientId, patient.getAdmissionDay(), patient.getRoomId(), patient.getOperationTheater()));

        ++counter;
    }

    solutionData.setPatients(outputPatients);

    const auto& nurses = problemData.getNurses();
    const auto& solutionAssignments = individual.getAssignments();
    std::vector<NurseOutputDTO> outputNurses;
    outputNurses.reserve((solutionAssignments.size()));

    if (nurses.size() != solutionAssignments.size())
    {
        throw std::invalid_argument("Representation of nurses is incorrect, something went wrong");
    }

    counter = 0;
    for (const auto& nurse : nurses)
    {
        const auto& assignments = solutionAssignments[counter];

        outputNurses.push_back(NurseOutputDTO(nurse.getId(), assignments));

        ++counter;
    }

    solutionData.setNurses(outputNurses);

    return solutionData;
}

std::string IHTCProblemIO::parseSolutionToJSON(const SolutionData& solution) const
{
    nlohmann::json jsonObject = solution;

    return jsonObject.dump(JSON_INDENT);
}
