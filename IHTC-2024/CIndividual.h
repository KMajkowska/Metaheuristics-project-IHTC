#pragma once
#include "Patient.h"
#include "Assignment.h"
#include "ICrosser.h"

#include<vector>

class IMutator;

class CIndividual
{
public:
	CIndividual();

	CIndividual(std::vector<Patient> patients, std::vector<std::vector<Assignment>> assignments);
	CIndividual(const CIndividual& otherIndividual) = default;

	std::vector<Patient> getPatients() const;
	std::vector<std::vector<Assignment>> getAssignments() const;
	double getFitness() const;
	bool isFitnessUpToDate() const;

	void setFitness(double newFitness);
	void setAssignments(std::vector<std::vector<Assignment>> newNurses);
	void setPatients(std::vector<Patient> newPatients);

	std::vector<CIndividual> crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const;
	void mute(const IMutator& mutator);
	std::vector<CIndividual> createNeighbours(const IMutator& mutator, int neighbourhoodNumber);

private:
	std::vector<Patient> patients;
	std::vector<std::vector<Assignment>> assignments;

	double fitness;
	bool fitnessUpToDate;
};