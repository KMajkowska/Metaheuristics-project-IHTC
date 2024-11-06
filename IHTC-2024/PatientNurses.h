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
	std::set<std::string> getNurses(const std::string& patientId);

	std::unordered_map<std::string, std::set<std::string>> getMap();

private:
	std::unordered_map<std::string, std::set<std::string>> occupantsAndPatientToNurses;

	static std::unordered_map<std::string, std::set<std::string>> processOccupantsAndPatients(const ProblemData& problemData);
};