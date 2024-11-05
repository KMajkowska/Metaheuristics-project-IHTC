#pragma once
#include "CIndividual.h"
#include "ProblemData.h"

struct PatientWrapper
{
public:
	PatientWrapper(const IncomingPatientDTO& newPatient, const ProblemData& newProblemData);

	int operator<=>(const PatientWrapper&) const;

private:
	const IncomingPatientDTO& patient;
	const ProblemData& problemData;
};