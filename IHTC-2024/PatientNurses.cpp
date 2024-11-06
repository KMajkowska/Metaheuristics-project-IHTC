#include "PatientNurses.h"

PatientNurses::PatientNurses(const ProblemData& problemData) :
    occupantsAndPatientToNurses(processOccupantsAndPatients(problemData))
{}

void PatientNurses::addNurse(const std::string& patientId, const std::string& nurseId)
{
    occupantsAndPatientToNurses.at(patientId).insert(nurseId);
}

std::set<std::string> PatientNurses::getNurses(const std::string& patientId)
{
    return occupantsAndPatientToNurses.at(patientId);
}

std::unordered_map<std::string, std::set<std::string>> PatientNurses::getMap()
{
    return occupantsAndPatientToNurses;
}

std::unordered_map<std::string, std::set<std::string>> PatientNurses::processOccupantsAndPatients(const ProblemData& problemData)
{
    const auto& patients = problemData.getPatients();
    const auto& occupants = problemData.getOccupants();

    std::unordered_map<std::string, std::set<std::string>> res;
    res.reserve(patients.size() + occupants.size());

    for (const auto& patient : patients)
    {
        std::set<std::string> newSet;
        
        res[patient.getId()] = newSet;
    }

    for (const auto& occupant : occupants)
    {
        std::set<std::string> newSet;

        res[occupant.getId()] = newSet;
    }

    return res
}
