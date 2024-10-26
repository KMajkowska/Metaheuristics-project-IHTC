#pragma once
#include "Patient.h"
#include "Assignment.h"
#include "IMutator.h"
#include "ICrosser.h"
#include<vector>

class CIndividual
{
public:
	CIndividual();

	CIndividual(std::vector<Patient> patients, std::vector<std::vector<Assignment>> assignments);

	std::vector<Patient> getPatients() const;
	std::vector<std::vector<Assignment>> getAssignments() const;
	double getFitness() const;
	bool isFitnessUpToDate() const;

	void setFitness(double newFitness);
	void setAssignments(std::vector<std::vector<Assignment>> newNurses);
	void setPatients(std::vector<Patient> newPatients);

	std::vector<CIndividual> crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const;
	void mute(const IMutator& mutator);

private:
	std::vector<Patient> patients;
	std::vector<std::vector<Assignment>> assignments;

	double fitness;
	bool fitnessUpToDate;
};