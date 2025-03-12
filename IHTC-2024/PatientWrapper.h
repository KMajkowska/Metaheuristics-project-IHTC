#pragma once

#include <compare>

#include "CIndividual.h"
#include "ProblemData.h"

/**
 * @brief Wrapper for patients class to allow us to compare two operating theaters and use this to choose
 *  which nurse is better to assign when we modify our solution
*/
struct PatientWrapper
{
	PatientWrapper(const IncomingPatientDTO& newPatient);

	std::strong_ordering operator<=>(const PatientWrapper&) const;

	IncomingPatientDTO patient;
};