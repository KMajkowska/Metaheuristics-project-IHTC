#include "IHTCMutatorOTInversion.h"

IHTCMutatorOTInversion::IHTCMutatorOTInversion(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability) :
	IHTCMutatorOperatingTheaters(randGenerator, problemData, newMutationProbability)
{}

bool IHTCMutatorOTInversion::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability)
	{
		return false;
	}

	std::uniform_int_distribution<int> day_distribution(0, _problemData.days() - 1);

	const int day { day_distribution(_randGenerator) };

	auto daysToOTs { getOperatingTheaterHelper(individual) };

	auto& ots { daysToOTs[day] };

	if (ots.size() < 2)
	{
		return false;
	}

	std::vector<std::string> keys;
	keys.reserve(ots.size());
	for (const auto& pair : ots) 
	{
		keys.push_back(pair.first);
	}

	auto patients { individual.patients() };

	std::shuffle(keys.begin(), keys.end(), _randGenerator);

	for (const auto& patientId : ots[keys[0]])
	{
		auto it = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& obj) {
			return obj.id() == patientId;
		});

		if (it != patients.end())
		{
			it->setOperationTheater(keys[1]);
		}
	}

	for (const auto& patientId : ots[keys[1]])
	{
		auto it = std::find_if(patients.begin(), patients.end(), [patientId](const Patient& obj) {
			return obj.id() == patientId;
		});

		if (it != patients.end())
		{
			it->setOperationTheater(keys[0]);
		}
	}

	individual.setPatients(patients);

	return true;
}

std::string IHTCMutatorOTInversion::mutatorName() const
{
	return "OperatingTheatersInversion";
}
