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
	const auto& rooms = problemData.getRooms();
	int days = problemData.getDays();

	std::uniform_int_distribution<int> patientDistribution(0, patients.size() - 1);

	Patient& patient = patients.at(patientDistribution(randGenerator));
	const auto patientFromProblem = problemData.getPatientMap().at(patient.getId());

	int countInvalidAdmissionDays = 0;

	int newAdmissionDay = randomDay(
		patientFromProblem.getSurgeryReleaseDay(), 
		patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay()
	);

	while (!checkCorrectAdmissionDay(newAdmissionDay, patientFromProblem.getSurgeonId(), patient.getOperationTheater()) 
		&& countInvalidAdmissionDays <= patientFromProblem.getLengthOfStay())
	{
		++countInvalidAdmissionDays;

		newAdmissionDay = randomDay(
			patientFromProblem.getSurgeryReleaseDay(),
			patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay()
		);
	}

	patient.setAdmissionDay(newAdmissionDay);

	individual.setPatients(patients);
}

std::string IHTCMutatorDay::getMutatorName() const
{
	return "Day";
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

bool IHTCMutatorDay::checkCorrectAdmissionDay(int admissionDay, const std::string& surgeonId, const std::string& otId) const
{
	if (admissionDay >= problemData.getDays())
	{
		return true;
	}

	const auto& otAvails = problemData.getOperatingTheatersAvailability();

	const auto& otAvail = otAvails.at(admissionDay);

	auto it = std::find_if(otAvail.begin(), otAvail.end(), [otId](const OperatingTheaterWrapper& wrapper)
		{
			return wrapper.operatingTheater.id == otId;
		}
	);

	bool isSurgeonAvailible = problemData.getSurgeonMap().at(surgeonId).getMaxSurgeryTime().at(admissionDay) > 0;

	return isSurgeonAvailible && it != otAvail.end();
}

