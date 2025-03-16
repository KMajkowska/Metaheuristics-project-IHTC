#include "IHTCMutatorAssignment.h"
#include "other.h"

IHTCMutatorAssignment::IHTCMutatorAssignment(
	std::mt19937& randGenerator,
	const ProblemData& problemData,
	double newSwapAssignmentsProbability
) :
	IMutator(randGenerator, problemData, newSwapAssignmentsProbability)
{}

bool IHTCMutatorAssignment::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability)
	{
		return false;
	}

	std::uniform_int_distribution<int> dayDistribution(0, _problemData.days() - 1);

	auto day { dayDistribution(_randGenerator) };

	auto assignments { individual.assignments() };

	if (assignments.empty())
	{
		return false;
	}

	std::uniform_int_distribution<size_t> assignmentsDistribution(0, assignments.size() - 1);

	auto nurseIt { assignments.begin() };
	std::advance(nurseIt, assignmentsDistribution(_randGenerator));

	if (nurseIt->second.empty())
	{
		return false;
	}
	
	std::uniform_int_distribution<size_t> nurseAssignmentOffset(0, nurseIt->second.size() - 1);
	std::uniform_int_distribution<size_t> roomsDistribution(0, _problemData.rooms().size() - 1);

	auto& nurseAssignment { nurseIt->second.at(nurseAssignmentOffset(_randGenerator)) };
	auto assignmentRooms { nurseAssignment.rooms() };

	std::string roomId { _problemData.rooms().at(roomsDistribution(_randGenerator)).id() };

	auto assignmentRoomIdIt { std::find(assignmentRooms.begin(), assignmentRooms.end(), roomId) };

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

std::string IHTCMutatorAssignment::mutatorName() const
{
	return "Assignment";
}
