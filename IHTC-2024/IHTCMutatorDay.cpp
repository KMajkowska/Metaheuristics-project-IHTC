#include "IHTCMutatorDay.h"

IHTCMutatorDay::IHTCMutatorDay(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability) :
	IMutator(randGenerator, problemData, newDayShuffleProbability)
{}

bool IHTCMutatorDay::mutate(CIndividual& individual) const
{
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	if (distribution(_randGenerator) > _mutationProbability)
	{
		return false;
	}

	auto patients { individual.patients() };
	const auto& rooms { _problemData.rooms() };
	int days { _problemData.days() };

	std::uniform_int_distribution<size_t> patientDistribution(0, patients.size() - 1);

	Patient& patient { patients.at(patientDistribution(_randGenerator)) };
	const auto patientFromProblem { _problemData.getPatientMap().at(patient.id()) };

	int countInvalidAdmissionDays { 1 };

	int newAdmissionDay { randomDay(
		patientFromProblem.getSurgeryReleaseDay(),
		patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay()
	) };

	while (!checkCorrectAdmissionDay(newAdmissionDay, patientFromProblem.getSurgeonId(), patient.operationTheater()) 
		&& countInvalidAdmissionDays <= patientFromProblem.lengthOfStay())
	{
		++countInvalidAdmissionDays;

		newAdmissionDay = randomDay(
			patientFromProblem.getSurgeryReleaseDay(),
			patientFromProblem.getSurgeryDueDay() > days ? days : patientFromProblem.getSurgeryDueDay()
		);
	}

	patient.setAdmissionDay(newAdmissionDay);

	individual.setPatients(patients);

	return true;
}

std::string IHTCMutatorDay::mutatorName() const
{
	return "Day";
}

// We allow to be greater than max, on purpose, it will be punished later
int IHTCMutatorDay::randomDay(int min, int max) const
{
	std::uniform_int_distribution<int> patientDistribution(min, max);

	return patientDistribution(_randGenerator);

	if (min == max)
	{
		return min;
	}

	double mean { min + 1.0 };
	double stddev { (max - min) / 6.0 };

	std::normal_distribution<double> distribution(mean, stddev);

	double day{ 0 };
	do 
	{
		day = distribution(_randGenerator);
	} 
	while (day <= min || day > max);

	return static_cast<int>(day);
}

bool IHTCMutatorDay::checkCorrectAdmissionDay(int admissionDay, const std::string& surgeonId, const std::string& otId) const
{
	if (admissionDay >= _problemData.days())
	{
		return true;
	}

	const auto& otAvails { _problemData.operatingTheatersAvailability() };
	const auto& otAvail { otAvails.at(admissionDay) };

	auto it
	{ 
		std::find_if(
		otAvail.begin(), otAvail.end(), [otId](const OperatingTheaterWrapper& wrapper)
		{
			return wrapper.operatingTheater().id() == otId;
		}) 
	};

	bool isSurgeonAvailible { _problemData.getSurgeonMap().at(surgeonId).maxSurgeryTime().at(admissionDay) > 0 };

	return isSurgeonAvailible && it != otAvail.end();
}

