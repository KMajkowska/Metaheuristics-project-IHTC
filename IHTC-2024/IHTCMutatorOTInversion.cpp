#include "IHTCMutatorOTInversion.h"

IHTCMutatorOTInversion::IHTCMutatorOTInversion(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability) :
	IHTCMutatorOperatingTheaters(randGenerator, problemData),
	mutationProbability(newMutationProbability)
{
	if (newMutationProbability > 1.0 || newMutationProbability < 0.0)
	{
		throw std::invalid_argument("OT inversion mutation probability is not in the range!");
	}
}

void IHTCMutatorOTInversion::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > mutationProbability)
	{
		return;
	}

	std::uniform_int_distribution<int> day_distribution(0, problemData.getDays() - 1);

	const int day = day_distribution(randGenerator);

	auto daysToOTs = getOperatingTheaterHelper(individual);

	auto& ots = daysToOTs[day];

	if (ots.size() < 2)
	{
		return;
	}

	std::vector<std::string> keys;
	keys.reserve(ots.size());
	for (const auto& pair : ots) 
	{
		keys.push_back(pair.first);
	}

	auto patients = individual.getPatients();

	std::shuffle(keys.begin(), keys.end(), randGenerator);

	for (const auto& patientId : ots[keys[0]])
	{
		auto it = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& obj) {
			return obj.getId() == patientId;
		});

		if (it != patients.end())
		{
			it->setOperationTheater(keys[1]);
		}
	}

	for (const auto& patientId : ots[keys[1]])
	{
		auto it = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& obj) {
			return obj.getId() == patientId;
		});

		if (it != patients.end())
		{
			it->setOperationTheater(keys[0]);
		}
	}

	individual.setPatients(patients);
}

std::string IHTCMutatorOTInversion::getMutatorName() const
{
	return "OperatingTheatersInversion";
}
