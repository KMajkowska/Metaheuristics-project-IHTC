#pragma once

#include <compare>

#include "CIndividual.h"
#include "ProblemData.h"

struct PatientWrapper
{
public:
	PatientWrapper(const IncomingPatientDTO& newPatient, const ProblemData& newProblemData);

	std::strong_ordering operator<=>(const PatientWrapper& other) const;

	const IncomingPatientDTO& patient;

private:
	const ProblemData& problemData;
};