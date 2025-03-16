#include "PatientWrapper.h"

PatientWrapper::PatientWrapper(const IncomingPatientDTO& newPatient) :
	_patient(newPatient)
{}

IncomingPatientDTO PatientWrapper::patient() const
{
	return _patient;
}

std::strong_ordering PatientWrapper::operator<=>(const PatientWrapper& other) const
{
	if (auto cmp = _patient.isMandatory() <=> other._patient.isMandatory(); cmp != 0) {
		return cmp;
	}

	if (auto cmp = other._patient.getSurgeryReleaseDay() <=> _patient.getSurgeryReleaseDay(); cmp != 0) {
		return cmp;
	}

	return _patient.lengthOfStay() <=> other._patient.lengthOfStay();
}
