#include "PatientNurses.h"

PatientNurses::PatientNurses(const ProblemData& problemData) :
    _occupantsAndPatientToNurses(processOccupantsAndPatients(problemData))
{}

void PatientNurses::addNurse(const std::string& patientId, const std::string& nurseId)
{
    _occupantsAndPatientToNurses.at(patientId).insert(nurseId);
}

std::set<std::string> PatientNurses::nurses(const std::string& patientId)
{
    return _occupantsAndPatientToNurses.at(patientId);
}

std::unordered_map<std::string, std::set<std::string>> PatientNurses::occupantsAndPatientToNurses()
{
    return _occupantsAndPatientToNurses;
}

std::unordered_map<std::string, std::set<std::string>> PatientNurses::processOccupantsAndPatients(const ProblemData& problemData)
{
    const auto& patients { problemData.patients() };
    const auto& occupants { problemData.occupants() };

    std::unordered_map<std::string, std::set<std::string>> res;
    res.reserve(patients.size() + occupants.size());

    for (const auto& patient : patients)
    {
        std::set<std::string> newSet;
        
        res[patient.id()] = newSet;
    }

    for (const auto& occupant : occupants)
    {
        std::set<std::string> newSet;

        res[occupant.id()] = newSet;
    }

    return res;
}
