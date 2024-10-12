#pragma once
#include "Patient.h"
#include "Assignment.h"
#include "IMutator.h"
#include "ICrosser.h"
#include<vector>

class CIndividual
{
public:
	std::vector <Patient> getPatients();
	std::vector<Assignment> getAssignments();
	void setAssignments(std::vector<Assignment> newNurses);
	void setPatients(std::vector<Patient> newPatients);
	void crossover(const CIndividual& otherIndividual, const ICrosser crosser);
	void mute(const IMutator mutator);

private:
	std::vector<Patient> patients;
	std::vector<Assignment> assignments;
	ICrosser crosser;
	IMutator mutator;
};