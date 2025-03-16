#include "GenderGrouper.h"

GenderGrouper::GenderGrouper(int perIterAmountFix, const ProblemData& problemData, std::mt19937& randGenerator) :
	_perIterAmountFix(perIterAmountFix),
	_problemData(problemData),
	_randGenerator(randGenerator)
{}

void GenderGrouper::greedyGroupGenders(CIndividual& individual) const
{
	auto rooms = _problemData.getPreprocessedRooms();
	auto patients = individual.patients();

	for (const auto& solutionPatient : patients)
	{
		const auto patient = _problemData.getPatientMap().at(solutionPatient.id());

		rooms.addIncomingPatient(solutionPatient.admissionDay(), solutionPatient.roomId(), patient);
	}

	std::string worstRoomId = "";
	int worstBrokenGenderAmount = -1;
	std::string worstGender = "";

	for (size_t i = 0; i < _problemData.days(); ++i)
	{
		for (const auto& roomsForDay : rooms.roomsForGivenDayRef(i))
		{
			for (const auto& [prevGenderName, prevGenderAmount] : roomsForDay.second._genders)
			{
				for (const auto& [genderName, amount] : roomsForDay.second._genders)
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

	for (size_t i { 0 }; i < _problemData.days(); ++i)
	{
		for (const auto& roomsForDay : rooms.roomsForGivenDayRef(i))
		{
			if ((roomsForDay.second._genders.size() == 1 && roomsForDay.second._genders.contains(worstGender))|| roomsForDay.second._genders.empty())
			{
				for (auto& solutionPatient : patients)
				{
					if (solutionPatient.roomId() == worstRoomId)
					{
						const auto patient = _problemData.getPatientMap().at(solutionPatient.id());

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

	std::uniform_int_distribution<size_t> roomRand(0, _problemData.rooms().size());

	for (auto& solutionPatient : patients)
	{
		if (solutionPatient.roomId() == worstRoomId)
		{
			const auto patient = _problemData.getPatientMap().at(solutionPatient.id());

			if (patient.gender() == worstGender)
			{
				solutionPatient.setRoomId(_problemData.rooms()[roomRand(_randGenerator)].id());
			}
		}
	}

	individual.setPatients(patients);
}

int GenderGrouper::iter() const
{
	return _perIterAmountFix;
}
