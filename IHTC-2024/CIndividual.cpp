#include "CIndividual.h"
#include "IMutator.h"

CIndividual::CIndividual(std::vector<Patient> patients, std::unordered_map<std::string, std::vector<Assignment>> assignments) :
	_patients(patients),
	_assignments(assignments)
{}

CIndividual::CIndividual(const CIndividual& otherIndividual) :
	_patients(otherIndividual._patients), // deep copy of the vector of Patients
	_assignments(otherIndividual._assignments), // deep copy of the map (string -> vector of Assignments)
	_fitness(otherIndividual._fitness),
	_violated(otherIndividual._violated),
	_fitnessUpToDate(otherIndividual._fitnessUpToDate),
	_mutatorName(otherIndividual._mutatorName)
{}

std::vector<Patient> CIndividual::patients() const
{
	return _patients;
}

std::unordered_map<std::string, std::vector<Assignment>> CIndividual::assignments() const
{
	return _assignments;
}

std::pair<double, ViolatedRestrictions> CIndividual::fitness() const
{
	if (!_fitnessUpToDate)
	{
		return std::make_pair(INT_MIN, _violated); // coertion
	}

	return std::make_pair(_fitness, _violated);
}

std::string CIndividual::mutatorName() const
{
	return _mutatorName;
}

bool CIndividual::isFitnessUpToDate() const
{
	return _fitnessUpToDate;
}

void CIndividual::setAssignments(std::unordered_map<std::string, std::vector<Assignment>> newAssignments)
{
	_assignments = newAssignments;
}

void CIndividual::setPatients(std::vector<Patient> newPatients)
{
	_patients = newPatients;
}

void CIndividual::setMutatorName(const std::string& newMutatorName)
{
	_mutatorName = newMutatorName;
}

void CIndividual::setFitness(const std::pair<double, ViolatedRestrictions>& newFitness)
{
	_fitnessUpToDate = true;
	_fitness = newFitness.first;
	_violated = newFitness.second;
}

std::vector<CIndividual> CIndividual::crossover(const CIndividual& otherIndividual, const ICrosser& crosser) const
{
	return crosser.crossover(*this, otherIndividual);
}

bool CIndividual::mute(const IMutator& mutator)
{
	_fitnessUpToDate = false;

	return mutator.mutate(*this);
}

std::vector<CIndividual> CIndividual::createNeighbours(const IMutator& mutator, int neighbourhoodNumber, const IProblem& problem)
{
	std::vector<CIndividual> neighbours;
	neighbours.reserve(neighbourhoodNumber);

	if (!this->_fitnessUpToDate)
	{
		setFitness(problem.eval(*this));
	}

	for (size_t i = 0; i < neighbourhoodNumber; ++i)
	{
		CIndividual individual(*this);
		bool isMutated = individual.mute(mutator);

		individual.setMutatorName(mutator.mutatorName());

		individual.setFitness(problem.eval(individual));
		
		if (isMutated)
		{
			neighbours.push_back(individual);
		}
	}

	return neighbours;
}

std::partial_ordering CIndividual::operator<=>(const CIndividual& other) const
{
	return _fitness <=> other._fitness;
}
