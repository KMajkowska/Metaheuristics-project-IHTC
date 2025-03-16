#include "IHTCMutatorOT.h"

IHTCMutatorOT::IHTCMutatorOT(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability) :
	IHTCMutatorOperatingTheaters(randGenerator, problemData, newMutationProbability)
{}

bool IHTCMutatorOT::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability || _problemData.operatingTheaters().size() <= 1)
	{
		return false;
	}

	auto patients { individual.patients() };
	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> otDistribution(0, _problemData.operatingTheaters().size() - 1);

	auto patientIt { patients.begin() };
	std::advance(patientIt, patientDistribution(_randGenerator));

	std::string oldItId { patientIt->operationTheater() };

	while (patientIt->operationTheater() == oldItId)
	{
		patientIt->setOperationTheater(_problemData.operatingTheaters().at(otDistribution(_randGenerator)).id());
	}

	individual.setPatients(patients);

	return true;
}

std::string IHTCMutatorOT::mutatorName() const
{
	return "OperatingTheater";
}
