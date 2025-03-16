#pragma once

#include "Patient.h"
#include "Assignment.h"
#include "ICrosser.h"
#include "ViolatedRestrictions.h"
#include "IProblem.h"

#include <vector>

class IMutator;

class CIndividual
{
public:
	CIndividual();

	CIndividual(std::vector<Patient> patients, std::unordered_map<std::string, std::vector<Assignment>> assignments);
	CIndividual(const CIndividual& otherIndividual);

	void setFitness(const std::pair<double, ViolatedRestrictions>& newFitness);
	void setAssignments(std::unordered_map<std::string, std::vector<Assignment>> newNurses);
	void setPatients(std::vector<Patient> newPatients);
	void setMutatorName(const std::string& mutatorName);

	std::vector<Patient> patients() const;
	std::unordered_map<std::string, std::vector<Assignment>> assignments() const;
	std::pair<double, ViolatedRestrictions> fitness() const;
	std::string mutatorName() const;
	bool isFitnessUpToDate() const;

	std::vector<CIndividual> crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const;
	bool mute(const IMutator& mutator);
	std::vector<CIndividual> createNeighbours(const IMutator& mutator, int neighbourhoodNumber, const IProblem& problem);

	std::partial_ordering operator<=>(const CIndividual&) const;

private:
	std::vector<Patient> _patients;
	std::unordered_map<std::string, std::vector<Assignment>> _assignments;

	double _fitness;
	bool _fitnessUpToDate;

	std::string _mutatorName { "" };

	ViolatedRestrictions _violated;
};