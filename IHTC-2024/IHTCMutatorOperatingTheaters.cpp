#include "IHTCMutatorOperatingTheaters.h"

IHTCMutatorOperatingTheaters::IHTCMutatorOperatingTheaters(std::mt19937& randGenerator, const ProblemData& problemData, double mutationProbability) :
	IMutator(randGenerator, problemData, mutationProbability)
{}

std::vector<std::unordered_map<std::string, std::vector<std::string>>> IHTCMutatorOperatingTheaters::getOperatingTheaterHelper(CIndividual& individual) const
{
	int days { _problemData.days() };
	const auto& patients { _problemData.patients() };

	auto copiedDaysToPatientsPerRoomMap { _problemData.getEmptyOperatingTheaters() };

	// begin :: fill in structure
	for (const auto& patient : individual.patients())
	{

		if (patient.admissionDay() < days)
		{
			auto& patientsPerRoom = copiedDaysToPatientsPerRoomMap.at(patient.admissionDay());

			auto it = patientsPerRoom.find(patient.operationTheater());

			if (it != patientsPerRoom.end())
			{
				patientsPerRoom.at(patient.operationTheater()).push_back(patient.id());
			}
		}
	}
	// end :: fill in structure

	return copiedDaysToPatientsPerRoomMap;
}
