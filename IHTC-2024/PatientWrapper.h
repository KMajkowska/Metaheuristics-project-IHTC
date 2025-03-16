#pragma once

#include <compare>

#include "CIndividual.h"
#include "ProblemData.h"

class PatientWrapper
{
public:
	PatientWrapper(const IncomingPatientDTO& newPatient);
	PatientWrapper(const PatientWrapper& newPatient) = default;

	IncomingPatientDTO patient() const;

	std::strong_ordering operator<=>(const PatientWrapper&) const;
private:
	IncomingPatientDTO _patient;
};