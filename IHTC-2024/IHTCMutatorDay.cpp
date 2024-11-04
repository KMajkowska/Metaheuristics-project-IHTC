#include "IHTCMutatorDay.h"

IHTCMutatorDay::IHTCMutatorDay(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability) :
	IMutator(randGenerator, problemData),
	dayShuffleProbability(newDayShuffleProbability)
{
	if (newDayShuffleProbability > 1.0 || newDayShuffleProbability < 0.0)
	{
		throw std::invalid_argument("Day shuffle probability is not in the range!");
	}
}

void IHTCMutatorDay::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(randGenerator) > dayShuffleProbability)
	{
		return;
	}

	auto patients = individual.getPatients();
	const auto& patientMap = problemData.getPatientMap();
	const auto& rooms = problemData.getRooms();
	int days = problemData.getDays();

	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);

	Patient& patient = patients.at(patientDistribution(randGenerator));
	const auto patientFromProblem = patientMap.at(patient.getId());

	int newAdmissionDay = randomDay(patientFromProblem.getSurgeryReleaseDay(), patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay());

	patient.setAdmissionDay(newAdmissionDay);

	individual.setPatients(patients);
}

// We allow to be greater than max, on purpose, it will be punished later
int IHTCMutatorDay::randomDay(int min, int max) const
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

