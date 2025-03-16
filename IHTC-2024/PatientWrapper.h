#pragma once

#include <compare>

#include "CIndividual.h"
#include "ProblemData.h"

/**
 * @brief Wrapper for patients class to allow us to compare two operating theaters and use this to choose
 *  which nurse is better to assign when we modify our solution
*/
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