#include "CIndividual.h"

CIndividual::CIndividual(std::vector<Patient> patients, std::vector<std::vector<Assignment>> assignments) :
	patients(patients),
	assignments(assignments)
{}

std::vector<Patient> CIndividual::getPatients() const
{
	return patients;
}

std::vector<std::vector<Assignment>> CIndividual::getAssignments() const
{
	return assignments;
}

void CIndividual::setAssignments(std::vector<std::vector<Assignment>> newAssignments)
{
	assignments = newAssignments;
}

void CIndividual::setPatients(std::vector<Patient> newPatients)
{
	patients = newPatients;
}

std::vector<CIndividual> CIndividual::crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const
{
	return crosser.crossover(*this, otherIndividual);
}

void CIndividual::mute(const IMutator& mutator)
{
	mutator.mutate(*this);
}