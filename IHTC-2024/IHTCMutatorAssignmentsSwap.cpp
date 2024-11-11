#include "IHTCMutatorAssignmentsSwap.h"
#include "other.h"

IHTCMutatorAssignmentsSwap::IHTCMutatorAssignmentsSwap(
	std::mt19937& randGenerator,
	const ProblemData& problemData,
	double newSwapAssignmentsProbability
) :
	IMutator(randGenerator, problemData),
	swapAssignmentsProbability(newSwapAssignmentsProbability)
{
	if (newSwapAssignmentsProbability > 1.0 || newSwapAssignmentsProbability < 0.0)
	{
		throw std::invalid_argument("Assignment swap probability is not in the range!");
	}
}

void IHTCMutatorAssignmentsSwap::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > swapAssignmentsProbability)
	{
		return;
	}

	std::uniform_int_distribution<int> dayDistribution(0, problemData.getDays() - 1);

	int day = dayDistribution(randGenerator);

	auto assignments = individual.getAssignments();

	// no possibility of two nurses omn the same day and shift
	if (assignments.size() < 2)
	{
		return;
	}

	std::uniform_int_distribution<int> assignmentsDistribution(0, assignments.size() - 1);

	auto firstNurseIt = assignments.begin();
	std::advance(firstNurseIt, assignmentsDistribution(randGenerator));

	if (firstNurseIt->second.empty())
	{
		return;
	}

	//	std::shuffle(assignments.begin(), assignments.end(), randGenerator);

	std::uniform_int_distribution<int> nurseAssignmentOffset(0, firstNurseIt->second.size() - 1);
	auto& _1stNurseAssignment = firstNurseIt->second.at(nurseAssignmentOffset(randGenerator));

	for (auto& [nurseId, nurseAssignments] : assignments)
	{
		if (nurseId == firstNurseIt->first)
		{
			continue;
		}

		for (auto& assignment : nurseAssignments)
		{
			if (_1stNurseAssignment.getDay() == assignment.getDay() && _1stNurseAssignment.getShift() == assignment.getShift())
			{
				auto _1stRooms = _1stNurseAssignment.getRooms();
				auto rooms = assignment.getRooms();

				if (_1stRooms.empty() || rooms.empty())
				{
					continue;
				}

				std::uniform_int_distribution<int> _1stNurseAssignmentRoomDistrib(0, _1stRooms.size() - 1);
				std::uniform_int_distribution<int> assignmentRoomDistrib(0, rooms.size() - 1);

				std::swap(
					_1stRooms[_1stNurseAssignmentRoomDistrib(randGenerator)],
					rooms[assignmentRoomDistrib(randGenerator)]
				);

				_1stNurseAssignment.setRooms(_1stRooms);
				assignment.setRooms(rooms);

				individual.setAssignments(assignments);

				return;
			}
		}
	}
}
