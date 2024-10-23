#include "IHTCProblem.h"

IHTCProblem::IHTCProblem(ProblemData& problemData) :
	problemData(problemData),
	roomInfos(problemData.getPreprocessedRooms())
{
	preprocessPatientsToRooms();
}

void IHTCProblem::preprocessPatientsToRooms()
{
	const auto& incomingPatients = problemData.getPatients();
	const auto& surgeonMap = problemData.getSurgeonMap();

	patientsInRoom.reserve(problemData.getDays());

	for (int i = 0; i < problemData.getDays(); ++i)
	{
		patientsInRoom.push_back(std::vector<int>(incomingPatients.size(), UNOCCUPIABLE));
	}

	for (int i = 0; i < incomingPatients.size(); ++i)
	{
		const IncomingPatientDTO& patient = incomingPatients[i];

		const int endOfPeriod = patient.isMandatory() ? patient.getSurgeryDueDay() : problemData.getDays();

		for (int j = patient.getSurgeryReleaseDay(); j < endOfPeriod; ++j)
		{
			const auto& surgeon = surgeonMap.at(patient.getSurgeonId());
			if (surgeon.getMaxSurgeryTime()[j] >= patient.getSurgeryDuration())
			{
				patientsInRoom[j][i] = ASSIGNABLE;
			}
		}
	}
}
