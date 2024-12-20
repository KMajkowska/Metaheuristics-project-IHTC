#include "IHTCMutatorOperatingTheaters.h"

IHTCMutatorOperatingTheaters::IHTCMutatorOperatingTheaters(std::mt19937& randGenerator, const ProblemData& problemData) :
	IMutator(randGenerator, problemData)
{}

std::vector<std::unordered_map<std::string, std::vector<std::string>>> IHTCMutatorOperatingTheaters::getOperatingTheaterHelper(CIndividual& individual) const
{
	int days = problemData.getDays();
	const auto& patients = problemData.getPatients();

	auto copiedDaysToPatientsPerRoomMap = problemData.getEmptyOperatingTheaters();

	// begin :: fill in structure
	for (const auto& patient : individual.getPatients())
	{

		if (patient.getAdmissionDay() < days)
		{
			auto& patientsPerRoom = copiedDaysToPatientsPerRoomMap.at(patient.getAdmissionDay());

			auto it = patientsPerRoom.find(patient.getOperationTheater());

			if (it != patientsPerRoom.end())
			{
				patientsPerRoom.at(patient.getOperationTheater()).push_back(patient.getId());
			}
		}
	}
	// end :: fill in structure

	return copiedDaysToPatientsPerRoomMap;
}
