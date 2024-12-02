#include "IHTCMutatorOT.h"

IHTCMutatorOT::IHTCMutatorOT(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability) :
	IHTCMutatorOperatingTheaters(randGenerator, problemData),
	mutationProbability(newMutationProbability)
{
	if (newMutationProbability > 1.0 || newMutationProbability < 0.0)
	{
		throw std::invalid_argument("OT inversion mutation probability is not in the range!");
	}
}

bool IHTCMutatorOT::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > mutationProbability || problemData.getOperatingTheaters().size() <= 1)
	{
		return false;
	}

	auto patients = individual.getPatients();
	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> otDistribution(0, problemData.getOperatingTheaters().size() - 1);

	auto patientIt = patients.begin();
	std::advance(patientIt, patientDistribution(randGenerator));

	std::string oldItId = patientIt->getOperationTheater();

	while (patientIt->getOperationTheater() == oldItId)
	{
		patientIt->setOperationTheater(problemData.getOperatingTheaters().at(otDistribution(randGenerator)).getId());
	}

	individual.setPatients(patients);

	return true;
}

std::string IHTCMutatorOT::getMutatorName() const
{
	return "OperatingTheater";
}
