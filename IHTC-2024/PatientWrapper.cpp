#include "PatientWrapper.h"

PatientWrapper::PatientWrapper(const IncomingPatientDTO& newPatient) :
	patient(newPatient)
{}

std::strong_ordering PatientWrapper::operator<=>(const PatientWrapper& other) const
{
	if (auto cmp = patient.isMandatory() <=> other.patient.isMandatory(); cmp != 0) {
		return cmp;
	}

	if (auto cmp = other.patient.getSurgeryReleaseDay() <=> patient.getSurgeryReleaseDay(); cmp != 0) {
		return cmp;
	}

	return patient.getLengthOfStay() <=> other.patient.getLengthOfStay();
}
