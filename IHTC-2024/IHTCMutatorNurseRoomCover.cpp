#include "IHTCMutatorNurseRoomCover.h"

IHTCMutatorNurseRoomCover::IHTCMutatorNurseRoomCover(
	std::mt19937& randGenerator,
	const ProblemData& problemData,
	double newRoomAddingToNurseProbability
) :
	IMutator(randGenerator, problemData),
	roomAddingToNurseProbability(newRoomAddingToNurseProbability)
{
	if (newRoomAddingToNurseProbability > 1.0 || newRoomAddingToNurseProbability < 0.0)
	{
		throw std::invalid_argument("Room adding to nurse probability is not in the range!");
	}
}

bool IHTCMutatorNurseRoomCover::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > roomAddingToNurseProbability || individual.getFitness().second.countUncoveredRoomHard <= 0)
	{
		return false;
	}

	auto rooms = problemData.getPreprocessedRooms();
	auto patients = individual.getPatients();

	for (const auto& solutionPatient : patients)
	{
		const auto patient = problemData.getPatientMap().at(solutionPatient.getId());

		rooms.addIncomingPatient(solutionPatient.getAdmissionDay(), solutionPatient.getRoomId(), patient);
	}

	auto nurses = individual.getAssignments();
	std::unordered_map<std::string, Assignment> nursesForDayAndShift;

	for (int i = 0; i < problemData.getDays(); ++i)
	{
		for (const auto& shiftName : problemData.getShiftTypes())
		{
			auto& room = rooms.getRoomsForGivenDayRef(i);
			for (auto& [roomId, roomInfo] : room)
			{
				if ((roomInfo.patientIds.size() > 0 || roomInfo.occupantIds.size() > 0) && roomInfo.nurseIdToShift.size() != problemData.getShiftTypes().size())
				{
					for (auto& [nurseId, nurseAssignments] : nurses)
					{
						for (auto& assignement : nurseAssignments)
						{
							if (assignement.getDay() == i && assignement.getShift() == shiftName)
							{
								nursesForDayAndShift[nurseId] = assignement;
							}
						}
					}

					auto nurseWithMinRooms = nursesForDayAndShift.begin();

					for (auto it = nursesForDayAndShift.begin(); it != nursesForDayAndShift.end(); ++it)
					{
						if (it->second.getRooms().size() < nurseWithMinRooms->second.getRooms().size())
						{
							nurseWithMinRooms = it;
						}
					}

					for (auto& assignement : nurses.at(nurseWithMinRooms->first))
					{
						if (assignement.getDay() == i && assignement.getShift() == shiftName)
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

std::string IHTCMutatorNurseRoomCover::getMutatorName() const
{
	return "NurseRoomCover";
}


