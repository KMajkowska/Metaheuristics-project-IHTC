#include "IHTCMutatorOTSwap.h"

IHTCMutatorOTSwap::IHTCMutatorOTSwap(std::mt19937& randGenerator, const ProblemData& problemData, double newMutationProbability) :
	IHTCMutatorOperatingTheaters(randGenerator, problemData),
	mutationProbability(newMutationProbability)
{
	if (newMutationProbability > 1.0 || newMutationProbability < 0.0)
	{
		throw std::invalid_argument("OT inversion mutation probability is not in the range!");
	}
}

void IHTCMutatorOTSwap::mutate(CIndividual& individual) const
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

	const std::string& otId0 = keys[0];
	const std::string& otId1 = keys[1];

	if (ots[otId0].size() <= 0 || ots[otId1].size() <= 0)
	{
		return;
	}

	std::uniform_int_distribution<int> ots0Distrib(0, ots[otId0].size() - 1);
	std::uniform_int_distribution<int> ots1Distrib(0, ots[otId1].size() - 1);

	const auto& patientId0 = ots[otId0][ots0Distrib(randGenerator)];
	const auto& patientId01 = ots[otId1][ots1Distrib(randGenerator)];

	auto it0 = std::find_if(patients.begin(), patients.end(), [otId0](const Patient& obj) {
		return obj.getId() == otId0;
	});

	if (it0 != patients.end())
	{
		it0->setOperationTheater(otId1);
	}

	auto it1 = std::find_if(patients.begin(), patients.end(), [otId1](const Patient& obj) {
		return obj.getId() == otId1;
	});

	if (it1 != patients.end())
	{
		it1->setOperationTheater(otId0);
	}

	individual.setPatients(patients);
}
