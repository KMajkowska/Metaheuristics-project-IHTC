#pragma once

#include <compare>

#include "CIndividual.h"
#include "ProblemData.h"

struct PatientWrapper
{
	PatientWrapper(const IncomingPatientDTO& newPatient);

	std::strong_ordering operator<=>(const PatientWrapper&) const;

	IncomingPatientDTO patient;
};