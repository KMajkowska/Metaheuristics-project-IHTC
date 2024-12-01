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

bool IHTCMutatorOTSwap::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > mutationProbability)
	{
		return false;
	}

	auto patients = individual.getPatients();
	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);

	while (true)
	{
		int idx0 = patientDistribution(randGenerator);
		int idx1 = patientDistribution(randGenerator);

		if (idx0 == idx1)
		{
			continue;
		}

		auto& patient0 = patients[idx0];
		auto& patient1 = patients[idx1];

		if (patient0.getOperationTheater() == patient1.getOperationTheater())
		{
			continue;
		}

		auto temp = patient0.getOperationTheater();

		patient0.setOperationTheater(patient1.getOperationTheater());
		patient1.setOperationTheater(temp);

		individual.setPatients(patients);

		return true;
	}

	//bool isFinished = false;

	//std::uniform_int_distribution<int> day_distribution(0, problemData.getDays() - 1);

	//while (!isFinished)
	//{
	//	const int day0 = day_distribution(randGenerator);
	//	const int day1 = day_distribution(randGenerator);

	//	auto daysToOTs = getOperatingTheaterHelper(individual);

	//	auto& ots0 = daysToOTs[day0];
	//	auto& ots1 = daysToOTs[day1];

	//	// don't swap if both are empty
	//	if (ots0.empty() || ots1.empty())
	//	{
	//		continue;
	//	}

	//	auto patients = individual.getPatients();

	//	std::uniform_int_distribution<int> ots0_distribution(0, ots0.size() - 1);
	//	std::uniform_int_distribution<int> ots1_distribution(0, ots1.size() - 1);

	//	auto itOts0 = ots0.begin();
	//	auto itOts1 = ots1.begin();

	//	std::advance(itOts0, ots0_distribution(randGenerator));
	//	std::advance(itOts1, ots1_distribution(randGenerator));

	//	const std::string& otId0 = itOts0->first;
	//	const std::string& otId1 = itOts1->first;

	//	if (ots0[otId0].empty() || ots1[otId1].empty() || otId0 == otId1 || day0 == day1)
	//	{
	//		continue;
	//	}

	//	std::uniform_int_distribution<int> ots0Distrib(0, ots0[otId0].size() - 1);
	//	std::uniform_int_distribution<int> ots1Distrib(0, ots1[otId1].size() - 1);

	//	const auto& patientId0 = ots0[otId0][ots0Distrib(randGenerator)];
	//	const auto& patientId1 = ots1[otId1][ots1Distrib(randGenerator)];

	//	auto it0 = std::find_if(patients.begin(), patients.end(), 
	//		[patientId0](const Patient& obj)
	//		{
	//			return obj.getId() == patientId0;
	//		}
	//	);

	//	auto it1 = std::find_if(patients.begin(), patients.end(),
	//		[patientId1](const Patient& obj)
	//		{
	//			return obj.getId() == patientId1;
	//		}
	//	);

	//	if (it0 == patients.end() || it1 == patients.end())
	//	{
	//		continue;
	//	}

	//	it0->setOperationTheater(otId1);
	//	it1->setOperationTheater(otId0);

	//	isFinished = true;

	//	individual.setPatients(patients);
	//}
}

std::string IHTCMutatorOTSwap::getMutatorName() const
{
	return "OperatingTheatersSwap";
}
