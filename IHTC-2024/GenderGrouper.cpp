#include "GenderGrouper.h"

GenderGrouper::GenderGrouper(int perIterAmountFix, const ProblemData& problemData, std::mt19937& randGenerator) :
	perIterAmountFix(perIterAmountFix),
	problemData(problemData),
	randGenerator(randGenerator)
{}

void GenderGrouper::greedyGroupGenders(CIndividual& individual) const
{
	auto rooms = problemData.getPreprocessedRooms();
	auto patients = individual.patients();

	for (const auto& solutionPatient : patients)
	{
		const auto patient = problemData.getPatientMap().at(solutionPatient.id());

		rooms.addIncomingPatient(solutionPatient.admissionDay(), solutionPatient.roomId(), patient);
	}

	std::string worstRoomId = "";
	int worstBrokenGenderAmount = -1;
	std::string worstGender = "";

	for (size_t i = 0; i < problemData.days(); ++i)
	{
		for (const auto& roomsForDay : rooms.roomsForGivenDayRef(i))
		{
			for (const auto& [prevGenderName, prevGenderAmount] : roomsForDay.second.genders)
			{
				for (const auto& [genderName, amount] : roomsForDay.second.genders)
				{
					if (genderName == prevGenderName)
					{
						continue;
					}

					int distance = abs(amount - prevGenderAmount);

					if (prevGenderAmount >= 0 && distance > worstBrokenGenderAmount)
					{
						worstRoomId = roomsForDay.first;
						worstBrokenGenderAmount = distance;
						worstGender = genderName;
					}
				}
			}
		}
	}

	if (worstGender.empty())
	{
		return;
	}

	for (size_t i = 0; i < problemData.days(); ++i)
	{
		for (const auto& roomsForDay : rooms.roomsForGivenDayRef(i))
		{
			if ((roomsForDay.second.genders.size() == 1 && roomsForDay.second.genders.contains(worstGender))|| roomsForDay.second.genders.empty())
			{
				for (auto& solutionPatient : patients)
				{
					if (solutionPatient.roomId() == worstRoomId)
					{
						const auto patient = problemData.getPatientMap().at(solutionPatient.id());

						if (patient.gender() == worstGender)
						{
							solutionPatient.setRoomId(roomsForDay.first);
						}
					}
				}

				individual.setPatients(patients);
				return;
			}
		}
	}

	std::uniform_int_distribution<int> roomRand(0, problemData.rooms().size());

	for (auto& solutionPatient : patients)
	{
		if (solutionPatient.roomId() == worstRoomId)
		{
			const auto patient = problemData.getPatientMap().at(solutionPatient.id());

			if (patient.gender() == worstGender)
			{
				solutionPatient.setRoomId(problemData.rooms()[roomRand(randGenerator)].id());
			}
		}
	}

	individual.setPatients(patients);
}

int GenderGrouper::getIter() const
{
	return perIterAmountFix;
}
