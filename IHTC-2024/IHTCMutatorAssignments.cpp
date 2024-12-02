#include "IHTCMutatorAssignment.h"
#include "other.h"

IHTCMutatorAssignment::IHTCMutatorAssignment(
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

bool IHTCMutatorAssignment::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > swapAssignmentsProbability)
	{
		return false;
	}

	std::uniform_int_distribution<int> dayDistribution(0, problemData.getDays() - 1);

	int day = dayDistribution(randGenerator);

	auto assignments = individual.getAssignments();

	if (assignments.empty())
	{
		return false;
	}

	std::uniform_int_distribution<size_t> assignmentsDistribution(0, assignments.size() - 1);

	auto nurseIt = assignments.begin();
	std::advance(nurseIt, assignmentsDistribution(randGenerator));

	if (nurseIt->second.empty())
	{
		return false;
	}
	
	std::uniform_int_distribution<size_t> nurseAssignmentOffset(0, nurseIt->second.size() - 1);
	std::uniform_int_distribution<size_t> roomsDistribution(0, problemData.getRooms().size() - 1);

	auto& nurseAssignment = nurseIt->second.at(nurseAssignmentOffset(randGenerator));
	auto assignmentRooms = nurseAssignment.getRooms();

	std::string roomId = problemData.getRooms().at(roomsDistribution(randGenerator)).getId();

	auto assignmentRoomIdIt = std::find(assignmentRooms.begin(), assignmentRooms.end(), roomId);

	if (assignmentRoomIdIt == assignmentRooms.end())
	{
		assignmentRooms.push_back(roomId);
	}
	else
	{
		assignmentRooms.erase(assignmentRoomIdIt);
	}

	nurseAssignment.setRooms(assignmentRooms);
	individual.setAssignments(assignments);

	return true;
}

std::string IHTCMutatorAssignment::getMutatorName() const
{
	return "Assignment";
}
