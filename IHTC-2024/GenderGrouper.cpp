#include "GenderGrouper.h"

GenderGrouper::GenderGrouper(int perIterAmountFix, const ProblemData& problemData, std::mt19937& randGenerator) :
	perIterAmountFix(perIterAmountFix),
	problemData(problemData),
	randGenerator(randGenerator)
{}

void GenderGrouper::greedyGroupGenders(CIndividual& individual) const
{
	auto rooms = problemData.getPreprocessedRooms();
	auto patients = individual.getPatients();

	for (const auto& solutionPatient : patients)
	{
		const auto patient = problemData.getPatientMap().at(solutionPatient.getId());

		rooms.addIncomingPatient(solutionPatient.getAdmissionDay(), solutionPatient.getRoomId(), patient);
	}

	std::string worstRoomId = "";
	int worstBrokenGenderAmount = -1;
	std::string worstGender = "";

	for (size_t i = 0; i < problemData.getDays(); ++i)
	{
		for (const auto& roomsForDay : rooms.getRoomsForGivenDayRef(i))
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

	for (size_t i = 0; i < problemData.getDays(); ++i)
	{
		for (const auto& roomsForDay : rooms.getRoomsForGivenDayRef(i))
		{
			if ((roomsForDay.second.genders.size() == 1 && roomsForDay.second.genders.contains(worstGender))|| roomsForDay.second.genders.empty())
			{
				for (auto& solutionPatient : patients)
				{
					if (solutionPatient.getRoomId() == worstRoomId)
					{
						const auto patient = problemData.getPatientMap().at(solutionPatient.getId());

						if (patient.getGender() == worstGender)
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

	std::uniform_int_distribution<int> roomRand(0, problemData.getRooms().size());

	for (auto& solutionPatient : patients)
	{
		if (solutionPatient.getRoomId() == worstRoomId)
		{
			const auto patient = problemData.getPatientMap().at(solutionPatient.getId());

			if (patient.getGender() == worstGender)
			{
				solutionPatient.setRoomId(problemData.getRooms()[roomRand(randGenerator)].getId());
			}
		}
	}

	individual.setPatients(patients);
}

int GenderGrouper::getIter() const
{
	return perIterAmountFix;
}
