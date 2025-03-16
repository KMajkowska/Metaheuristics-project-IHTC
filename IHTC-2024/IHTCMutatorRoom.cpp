#include "IHTCMutatorRoom.h"

IHTCMutatorRoom::IHTCMutatorRoom(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomShuffleProbability) :
	IMutator(randGenerator, problemData, newRoomShuffleProbability)
{}

bool IHTCMutatorRoom::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability)
	{
		return false;
	}

	auto patients = individual.patients();
	const auto& rooms = _problemData.rooms();

	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> roomDistribution(0, rooms.size() - 1);

	Patient& patient = patients.at(patientDistribution(_randGenerator));

	std::string oldRoom { patient.roomId() };
	
	while (patient.roomId() == oldRoom)
	{
		patient.setRoomId(rooms.at(roomDistribution(_randGenerator)).id());
	}

	individual.setPatients(patients);

	return true;
}
std::string IHTCMutatorRoom::mutatorName() const
{
	return "Room";
}
