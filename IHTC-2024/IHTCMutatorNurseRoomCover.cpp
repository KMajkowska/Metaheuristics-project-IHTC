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

void IHTCMutatorNurseRoomCover::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > roomAddingToNurseProbability)
	{
		return;
	}

	std::uniform_int_distribution<int> dayDistribution(0, problemData.getDays() - 1);
	std::uniform_int_distribution<int> shiftDistribution(0, problemData.getShiftTypes().size() - 1);

	int day = dayDistribution(randGenerator);
	int shiftNumber = shiftDistribution(randGenerator);
	std::string shiftName = problemData.getShiftTypes()[shiftNumber];

	auto nurses = individual.getAssignments();
	std::unordered_map<std::string, Assignment> nursesForDayAndShift;

	for (auto& nurse : nurses)
	{
		for (auto& assignement : nurse.second)
		{
			if (assignement.getDay() == day && assignement.getShift() == shiftName)
			{
				nursesForDayAndShift[nurse.first] = assignement;
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

	auto rooms = problemData.getPreprocessedRooms().getRoomsForGivenDayRef(day);

	for (auto& room : rooms)
	{
		if (room.second.patientIds.size() != 0 && room.second.nurseIdToShift.size() == 0)
		{
			nurseWithMinRooms->second.appendRoom(room.first);
		}
	}

	std::find_if(nurses[nurseWithMinRooms->first].begin(), nurses[nurseWithMinRooms->first].end(), [nurseWithMinRooms](const Assignment& assignment)
		{
			return assignment.getDay() == nurseWithMinRooms->second.getDay() && assignment.getShift() == nurseWithMinRooms->second.getShift();
		}
	);

	individual.setAssignments(nurses);
}

std::string IHTCMutatorNurseRoomCover::getMutatorName() const
{
	return "NurseRoomCover";
}


