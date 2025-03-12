#pragma once

#include "Patient.h"
#include "Assignment.h"
#include "ICrosser.h"
#include "ViolatedRestrictions.h"
#include "IProblem.h"

#include <vector>

class IMutator;

/**
 * @brief Main Individual for all our solvers. It is our solution. 
 * Individual is created solution, changing in every iteration.
 * it contains list of patients, assigned to room, OT and day 
 * moreover contains map nurseId to theirs assignemnts
*/
class CIndividual
{
public:
	CIndividual();

	CIndividual(std::vector<Patient> patients, std::unordered_map<std::string, std::vector<Assignment>> assignments);
	CIndividual(const CIndividual& otherIndividual);

	std::vector<Patient> getPatients() const;
	std::unordered_map<std::string, std::vector<Assignment>> getAssignments() const;
	std::pair<double, ViolatedRestrictions> getFitness() const;
	std::string getMutatorName() const;
	bool isFitnessUpToDate() const;

	void setFitness(const std::pair<double, ViolatedRestrictions>& newFitness);
	void setAssignments(std::unordered_map<std::string, std::vector<Assignment>> newNurses);
	void setPatients(std::vector<Patient> newPatients);
	void setMutatorName(const std::string& mutatorName);

	std::vector<CIndividual> crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const;
	bool mute(const IMutator& mutator);
	std::vector<CIndividual> createNeighbours(const IMutator& mutator, int neighbourhoodNumber, const IProblem& problem);

	std::partial_ordering operator<=>(const CIndividual&) const;

private:
	std::vector<Patient> patients;
	std::unordered_map<std::string, std::vector<Assignment>> assignments;

	double fitness;
	ViolatedRestrictions violated;
	bool fitnessUpToDate;

	std::string mutatorName = "";
};