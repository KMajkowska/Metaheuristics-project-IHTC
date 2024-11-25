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

CIndividual::CIndividual(const CIndividual& otherIndividual) :
	patients(otherIndividual.patients), // deep copy of the vector of Patients
	assignments(otherIndividual.assignments), // deep copy of the map (string -> vector of Assignments)
	fitness(otherIndividual.fitness),
	violated(otherIndividual.violated),
	fitnessUpToDate(otherIndividual.fitnessUpToDate),
	mutatorName(otherIndividual.mutatorName)
{}

std::vector<Patient> CIndividual::getPatients() const
{
	return patients;
}

std::unordered_map<std::string, std::vector<Assignment>> CIndividual::getAssignments() const
{
	return assignments;
}

std::pair<double, ViolatedRestrictions> CIndividual::getFitness() const
{
	if (!fitnessUpToDate)
	{
		return std::make_pair(INT_MIN, violated); // coertion
	}

	return std::make_pair(fitness, violated);
}

std::string CIndividual::getMutatorName() const
{
	return mutatorName;
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

void CIndividual::setMutatorName(const std::string& newMutatorName)
{
	mutatorName = newMutatorName;
}

void CIndividual::setFitness(const std::pair<double, ViolatedRestrictions>& newFitness)
{
	fitnessUpToDate = true;
	fitness = newFitness.first;
	violated = newFitness.second;
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

std::vector<CIndividual> CIndividual::createNeighbours(const IMutator& mutator, int neighbourhoodNumber, const IProblem& problem)
{
	std::vector<CIndividual> neighbours;
	neighbours.reserve(neighbourhoodNumber);

	if (!this->fitnessUpToDate)
	{
		setFitness(problem.eval(*this));
	}

	for (size_t i = 0; i < neighbourhoodNumber; ++i)
	{
		CIndividual individual(*this);
		individual.mute(mutator);

		individual.setMutatorName(mutator.getMutatorName());

		individual.setFitness(problem.eval(individual));
		
		/*if (violated != individual.violated) 
		{*/
			neighbours.push_back(individual);
		//}
	}

	return neighbours;
}

std::partial_ordering CIndividual::operator<=>(const CIndividual& other) const
{
	return fitness <=> other.fitness;
}
