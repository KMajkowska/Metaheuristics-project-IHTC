#pragma once

#include <unordered_map>
#include <string>
#include <set>

#include "ProblemData.h"

/**
 * @brief Class where we store the info how muny nurses has a patient during his stay at hospital
 * Based on it the soft restriction continous of care (minimazing the number of n urses taking care of the patient) is calculated
*/
class PatientNurses
{
public:
	PatientNurses(const ProblemData& problemData);
	PatientNurses(const PatientNurses& other) = default;
	
	void addNurse(const std::string& patientId, const std::string& nurseId);
	std::set<std::string> getNurses(const std::string& patientId);

	std::unordered_map<std::string, std::set<std::string>> getMap();

private:
	std::unordered_map<std::string, std::set<std::string>> occupantsAndPatientToNurses;

	static std::unordered_map<std::string, std::set<std::string>> processOccupantsAndPatients(const ProblemData& problemData);
};