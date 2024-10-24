#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(ProblemData& problemData, const std::function<double(const WeightsDTO&, const ViolatedRestrictions&)>& evalFn) :
	problemData(problemData),
	roomInfos(problemData.getPreprocessedRooms()),
	evalFn(evalFn)
{
	preprocessPatientsToRooms();
}

double IHTCProblem::eval(const CIndividual& individual) const
{
	return evalFn(
		problemData.getWeights(), 
		getViolatedFromSolution(
			problemData, 
			IHTCProblemIO::parseToSolution(individual, problemData)
		)
	);
}

void IHTCProblem::preprocessPatientsToRooms()
{
	const auto& incomingPatients = problemData.getPatients();
	const auto& surgeonMap = problemData.getSurgeonMap();
	const int days = problemData.getDays();

	patientsInRoom.reserve(days);

	for (int dayIdx = 0; dayIdx < days; ++dayIdx)
	{
		patientsInRoom.push_back(std::vector<int>(incomingPatients.size(), UNOCCUPIABLE));
	}

	for (int patientIdx = 0; patientIdx < incomingPatients.size(); ++patientIdx)
	{
		const IncomingPatientDTO& patient = incomingPatients[patientIdx];

		const int endOfPeriod = patient.isMandatory() ? patient.getSurgeryDueDay() : days;

		for (int dayIdx = patient.getSurgeryReleaseDay(); dayIdx < endOfPeriod; ++dayIdx)
		{
			const auto& surgeon = surgeonMap.at(patient.getSurgeonId());

			if (surgeon.getMaxSurgeryTime()[dayIdx] >= patient.getSurgeryDuration())
			{
				patientsInRoom[dayIdx][patientIdx] = ASSIGNABLE;
			}
		}

		for (int dayIdx = endOfPeriod; dayIdx < days; ++dayIdx)
		{
			patientsInRoom[dayIdx][patientIdx] = UNDESIRED;
		}
	}
}
