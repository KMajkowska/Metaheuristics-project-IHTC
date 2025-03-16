#include "IHTCMutatorNurseRoomCover.h"

IHTCMutatorNurseRoomCover::IHTCMutatorNurseRoomCover(
	std::mt19937& randGenerator,
	const ProblemData& problemData,
	double newRoomAddingToNurseProbability
) :
	IMutator(randGenerator, problemData, newRoomAddingToNurseProbability)
{
	if (newRoomAddingToNurseProbability > 1.0 || newRoomAddingToNurseProbability < 0.0)
	{
		throw std::invalid_argument("Room adding to nurse probability is not in the range!");
	}
}

bool IHTCMutatorNurseRoomCover::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability || individual.fitness().second.countUncoveredRoomHard <= 0)
	{
		return false;
	}

	auto rooms { _problemData.getPreprocessedRooms() };
	auto patients { individual.patients() };

	for (const auto& solutionPatient : patients)
	{
		const auto patient { _problemData.getPatientMap().at(solutionPatient.id()) };

		rooms.addIncomingPatient(solutionPatient.admissionDay(), solutionPatient.roomId(), patient);
	}

	auto nurses { individual.assignments() };
	std::unordered_map<std::string, Assignment> nursesForDayAndShift;

	for (int i = 0; i < _problemData.days(); ++i)
	{
		for (const auto& shiftName : _problemData.shiftTypes())
		{
			auto& room { rooms.roomsForGivenDayRef(i) };
			for (auto& [roomId, roomInfo] : room)
			{
				if ((roomInfo.patientIds().size() > 0 || roomInfo.occupantIds.size() > 0) && roomInfo.nurseIdToShift().size() != _problemData.shiftTypes().size())
				{
					for (auto& [nurseId, nurseAssignments] : nurses)
					{
						for (auto& assignement : nurseAssignments)
						{
							if (assignement.day() == i && assignement.shift() == shiftName)
							{
								nursesForDayAndShift[nurseId] = assignement;
							}
						}
					}

					auto nurseWithMinRooms { nursesForDayAndShift.begin() };

					for (auto it = nursesForDayAndShift.begin(); it != nursesForDayAndShift.end(); ++it)
					{
						if (it->second.rooms().size() < nurseWithMinRooms->second.rooms().size())
						{
							nurseWithMinRooms = it;
						}
					}

					for (auto& assignement : nurses.at(nurseWithMinRooms->first))
					{
						if (assignement.day() == i && assignement.shift() == shiftName)
						{
							assignement.appendRoom(roomId);
							rooms.addAssignment(i, roomId, shiftName, nurseWithMinRooms->first);
						}
					}
				}
			}
		}
	}

	individual.setAssignments(nurses);

	return true;
}

std::string IHTCMutatorNurseRoomCover::mutatorName() const
{
	return "NurseRoomCover";
}


