#pragma once

#include <unordered_map>
#include <string>
#include <set>

#include "ProblemData.h"

class PatientNurses
{
public:
	PatientNurses(const ProblemData& problemData);
	PatientNurses(const PatientNurses& other) = default;
	
	void addNurse(const std::string& patientId, const std::string& nurseId);

	std::set<std::string> nurses(const std::string& patientId);
	std::unordered_map<std::string, std::set<std::string>> occupantsAndPatientToNurses();

private:
	std::unordered_map<std::string, std::set<std::string>> _occupantsAndPatientToNurses;

	static std::unordered_map<std::string, std::set<std::string>> processOccupantsAndPatients(const ProblemData& problemData);
};