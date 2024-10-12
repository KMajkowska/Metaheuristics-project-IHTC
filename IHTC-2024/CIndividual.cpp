#include "CIndividual.h"

std::vector <Patient> CIndividual::getPatients()
{
	return patients;
}

std::vector<Assignment> CIndividual::getAssignments()
{
	return assignments;
}

void CIndividual::setAssignments(std::vector<Assignment> newAssignments)
{
	assignments = newAssignments;
}

void CIndividual::setPatients(std::vector<Patient> newPatients)
{
	patients = newPatients;
}

void CIndividual::crossover(const CIndividual& otherIndividual, const ICrosser crosser)
{

}

void CIndividual::mute(const IMutator mutator)
{

}