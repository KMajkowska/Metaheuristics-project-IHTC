#include "IHTCMutatorRoom.h"

IHTCMutatorRoom::IHTCMutatorRoom(std::mt19937& randGenerator, const ProblemData& problemData, double newRoomShuffleProbability) :
	IMutator(randGenerator, problemData),
	roomShuffleProbability(newRoomShuffleProbability)
{
	if (newRoomShuffleProbability > 1.0 || newRoomShuffleProbability < 0.0)
	{
		throw std::invalid_argument("Room shuffle probability is not in the range!");
	}
}

bool IHTCMutatorRoom::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > roomShuffleProbability)
	{
		return false;
	}

	auto patients = individual.getPatients();
	const auto& rooms = problemData.getRooms();

	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> roomDistribution(0, rooms.size() - 1);

	Patient& patient = patients.at(patientDistribution(randGenerator));

	std::string oldRoom = patient.getRoomId();
	
	while (patient.getRoomId() == oldRoom)
	{
		patient.setRoomId(rooms.at(roomDistribution(randGenerator)).getId());
	}

	individual.setPatients(patients);

	return true;
}
std::string IHTCMutatorRoom::getMutatorName() const
{
	return "Room";
}
