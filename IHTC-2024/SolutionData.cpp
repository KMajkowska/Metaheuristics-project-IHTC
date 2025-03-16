#include "SolutionData.h"

SolutionData::SolutionData(const ProblemData& problemData, const CIndividual& individual) :
    _patients(individual.patients()),
    _nurses([&]() 
            {
                const auto& nurses = problemData.nurses();
                const auto& solutionAssignments = individual.assignments();

                if (nurses.size() != solutionAssignments.size()) 
                {
                    throw std::invalid_argument("Representation of nurses is incorrect, something went wrong");
                }

                std::vector<NurseOutputDTO> tempOutputNurses;
                tempOutputNurses.reserve(solutionAssignments.size());

                for (const auto& nurse : nurses) 
                {
                    tempOutputNurses.emplace_back(nurse.id(), solutionAssignments.at(nurse.id()));
                }

                return tempOutputNurses;
            }())
{}

std::vector<NurseOutputDTO> SolutionData::nurses() const
{
    return _nurses;
}

std::vector<Patient> SolutionData::patients() const
{
    return _patients;
}

void SolutionData::setNurses(std::vector<NurseOutputDTO> newNurses)
{
    _nurses = newNurses;
}

void SolutionData::setPatients(std::vector<Patient> newPatients)
{
    _patients = newPatients;
}

void to_json(nlohmann::json& j, const SolutionData& data)
{
    j = nlohmann::json
    {
        {"nurses", data.nurses()},
        {"patients", data.patients()},
    };
}

void from_json(const nlohmann::json& j, SolutionData& data)
{
    data.setNurses(j.at("nurses").get<std::vector<NurseOutputDTO>>());
    data.setPatients(j.at("patients").get<std::vector<Patient>>());
}
