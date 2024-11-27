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

void IHTCMutatorRoom::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	if (distribution(randGenerator) > roomShuffleProbability)
	{
		return;
	}

	auto patients = individual.getPatients();
	const auto& patientMap = problemData.getPatientMap();
	const auto& rooms = problemData.getRooms();
	auto roomsMap = problemData.getPreprocessedRooms();

	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> roomDistribution(0, rooms.size() - 1);

	Patient& patient = patients.at(patientDistribution(randGenerator));
	while (patient.getAdmissionDay() >= problemData.getDays() || patient.getAdmissionDay() < 0)
	{
		patient = patients.at(patientDistribution(randGenerator));
	}

	for (int i = 0; i < patients.size(); ++i)
	{
		const Patient& patient = patients[i];
		const IncomingPatientDTO incomingPatient = patientMap.at(patient.getId());
		roomsMap.addIncomingPatient(patient.getAdmissionDay(), patient.getRoomId(), incomingPatient);
	}

	const IncomingPatientDTO incomingPatient = patientMap.at(patient.getId());
	std::string oldRoom = patient.getRoomId();

	for (int i = 0; i < rooms.size(); ++i)
	{	
		auto& roomInfo = roomsMap.getPatientRoomInfoRef(patient.getAdmissionDay(), rooms[i].getId());
		if (roomInfo.currentCapacity > 0)
		{
			patient.setRoomId(rooms[i].getId());

			auto it = roomInfo.genders.find(incomingPatient.getGender());
			
			if (roomInfo.genders.size() <= 1 && it == roomInfo.genders.end())
			{
				patient.setRoomId(oldRoom);
			}
		}
	}

	/*if (patient.getRoomId() == oldRoom)
	{
		patient.setRoomId(rooms.at(roomDistribution(randGenerator)).getId());
	}*/

	individual.setPatients(patients);
}

std::string IHTCMutatorRoom::getMutatorName() const
{
	return "Room";
}
