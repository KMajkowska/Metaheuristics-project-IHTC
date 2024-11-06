#include "PatientWrapper.h"

PatientWrapper::PatientWrapper(const IncomingPatientDTO& newPatient,const ProblemData& newProblemData) :
	patient(newPatient),
	problemData(newProblemData)
{}

auto PatientWrapper::operator<=>(const PatientWrapper& other) const
{

	if (patient.isMandatory() != other.patient.isMandatory())
	{
		return patient.isMandatory() ? 1 : -1;
	}

	if (patient.getSurgeryReleaseDay() != other.patient.getSurgeryReleaseDay())
	{
		return patient.getSurgeryReleaseDay() < other.patient.getSurgeryReleaseDay() ? 1 : -1;
	}

	if (patient.getLengthOfStay() != other.patient.getLengthOfStay())
	{
		return patient.getLengthOfStay() > other.patient.getLengthOfStay() ? 1 : -1;
	}

	return 0;
}
