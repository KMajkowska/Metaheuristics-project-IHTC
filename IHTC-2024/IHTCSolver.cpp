#include "IHTCSolver.h"

IHTCSolver::IHTCSolver(const ProblemData& newProblemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
	roomInfos(newProblemData.getPreprocessedRooms()),
	ISolver(newProblemData, randGenerator),
	consumer(consumer)
{
	preprocessPatientsToRooms();
}

void IHTCSolver::preprocessPatientsToRooms()
{
	const auto& incomingPatients = problemData.patients();
	const auto& surgeonMap = problemData.getSurgeonMap();
	const int days = problemData.days();

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
			const auto surgeon = surgeonMap.at(patient.getSurgeonId());

			if (surgeon.maxSurgeryTime()[dayIdx] >= patient.getSurgeryDuration())
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
