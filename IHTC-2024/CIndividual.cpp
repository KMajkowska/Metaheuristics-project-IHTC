#include "CIndividual.h"
#include "IMutator.h"

CIndividual::CIndividual() : 
	fitness(0),
	fitnessUpToDate(false)
{
}

CIndividual::CIndividual(std::vector<Patient> patients, std::unordered_map<std::string, std::vector<Assignment>> assignments) :
	patients(patients),
	assignments(assignments),
	fitness(0),
	fitnessUpToDate(false)
{}

std::vector<Patient> CIndividual::getPatients() const
{
	return patients;
}

std::unordered_map<std::string, std::vector<Assignment>> CIndividual::getAssignments() const
{
	return assignments;
}

double CIndividual::getFitness() const
{
	if (!fitnessUpToDate)
	{
		return INT_MIN; // coertion
	}

	return fitness;
}

bool CIndividual::isFitnessUpToDate() const
{
	return fitnessUpToDate;
}

void CIndividual::setAssignments(std::unordered_map<std::string, std::vector<Assignment>> newAssignments)
{
	assignments = newAssignments;
}

void CIndividual::setPatients(std::vector<Patient> newPatients)
{
	patients = newPatients;
}

void CIndividual::setFitness(double newFitness)
{
	fitnessUpToDate = true;
	fitness = newFitness;
}

std::vector<CIndividual> CIndividual::crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const
{
	return crosser.crossover(*this, otherIndividual);
}

void CIndividual::mute(const IMutator& mutator)
{
	fitnessUpToDate = false;

	mutator.mutate(*this);
}

std::vector<CIndividual> CIndividual::createNeighbours(const IMutator& mutator, int neighbourhoodNumber) const
{
	std::vector<CIndividual> neighbours;
	neighbours.reserve(neighbourhoodNumber);

	for (size_t i = 0; i < neighbourhoodNumber; ++i)
	{
		CIndividual individual(*this);
		individual.mute(mutator);
		neighbours.push_back(individual);
	}

	return neighbours;
}