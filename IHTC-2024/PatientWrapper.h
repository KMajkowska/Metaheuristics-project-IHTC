#pragma once
#include "CIndividual.h"
#include "ProblemData.h"

struct PatientWrapper
{
public:
	PatientWrapper(const IncomingPatientDTO& newPatient, const ProblemData& newProblemData);

	auto operator<=>(const PatientWrapper&) const;

	const IncomingPatientDTO& patient;

private:
	const ProblemData& problemData;
};