#include "IHTCMutator.h"

IHTCMutator::IHTCMutator(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability, double newRoomShuffleProbability) :
	IMutator(randGenerator, problemData)
{
	if (newDayShuffleProbability > 1.0 || newDayShuffleProbability < 0.0)
		throw std::invalid_argument("Day shuffle probability is not in the range!");

	if (newRoomShuffleProbability > 1.0 || newRoomShuffleProbability < 0.0)
		throw std::invalid_argument("Room shuffle probability is not in the range!");

	roomShuffleProbability = newRoomShuffleProbability;
	dayShuffleProbability = newDayShuffleProbability;
}

void IHTCMutator::mutate(CIndividual& individual) const
{
	auto patients = individual.getPatients();
	const auto& patientMap = problemData.getPatientMap();
	const auto& rooms = problemData.getRooms();
	int days = problemData.getDays();

	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);
	std::uniform_int_distribution<int> roomDistribution(0, rooms.size() - 1);

	Patient& patient = patients.at(patientDistribution(randGenerator));
	const auto patientFromProblem = patientMap.at(patient.getId());

	if (distribution(randGenerator) <= dayShuffleProbability)
	{
		int newAdmissionDay = randomDay(patientFromProblem.getSurgeryReleaseDay(), patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay());

		patient.setAdmissionDay(newAdmissionDay);
	}

	if (distribution(randGenerator) <= roomShuffleProbability)
	{
		patient.setRoomId(rooms.at(roomDistribution(randGenerator)).getId());
	}

	individual.setPatients(patients);
}

// We allow to be greater than max, on purpose, it will be punished later
int IHTCMutator::randomDay(int min, int max) const
{
	if (min == max)
	{
		return min;
	}

	double mean = (min + max) / 2.0;
	double stddev = (max - min) / 6.0;

	std::normal_distribution<double> distribution(mean, stddev);

	double day;
	do {
		day = distribution(randGenerator);
	} while (day < min);


	return static_cast<int>(day);
}

