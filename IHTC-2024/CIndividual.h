#pragma once

#include "Patient.h"
#include "Assignment.h"
#include "ICrosser.h"
#include "ViolatedRestrictions.h"

#include <vector>
#include "IProblem.h"

class IMutator;

class CIndividual
{
public:
	CIndividual();

	CIndividual(std::vector<Patient> patients, std::unordered_map<std::string, std::vector<Assignment>> assignments);
	CIndividual(const CIndividual& otherIndividual);

	std::vector<Patient> getPatients() const;
	std::unordered_map<std::string, std::vector<Assignment>> getAssignments() const;
	std::pair<double, ViolatedRestrictions> getFitness() const;
	bool isFitnessUpToDate() const;

	void setFitness(const std::pair<double, ViolatedRestrictions>& newFitness);
	void setAssignments(std::unordered_map<std::string, std::vector<Assignment>> newNurses);
	void setPatients(std::vector<Patient> newPatients);

	std::vector<CIndividual> crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const;
	void mute(const IMutator& mutator);
	std::vector<CIndividual> createNeighbours(const IMutator& mutator, int neighbourhoodNumber, const IProblem& problem);

private:
	std::vector<Patient> patients;
	std::unordered_map<std::string, std::vector<Assignment>> assignments;

	double fitness;
	ViolatedRestrictions violated;
	bool fitnessUpToDate;
};