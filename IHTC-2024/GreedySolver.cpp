#include "GreedySolver.h"

GreedySolver::GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator) : 
	IHTCSolver(problemData, randGenerator) 
{}

CIndividual GreedySolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	int days = problemData.getDays();
	auto preprocessedRooms = problemData.getPreprocessedRooms();
	
	// begin :: ots
	std::vector<std::vector<OperatingTheaterWrapper>> operatingTheaters;
	operatingTheaters.reserve(problemData.getOperatingTheaters().size());

	for (int i = 0; i < days; ++i)
	{
		for (const auto& operatingTheater : problemData.getOperatingTheaters())
		{
			operatingTheaters[i].push_back(
				OperatingTheaterWrapper(
					OperatingTheaterInfo(operatingTheater.getAvailability()[i], 0, operatingTheater.getId())
				)
			);
		}

		std::make_heap(operatingTheaters[i].begin(), operatingTheaters[i].end());
	}
	// end :: ots

	// begin :: surgeons
	std::unordered_map<std::string, SurgeryTimeActualToMax> surgeons;
	surgeons.reserve(problemData.getSurgeons().size());

	for (const auto& surgeon : problemData.getSurgeons())
	{
		surgeons[surgeon.getId()] = SurgeryTimeActualToMax(surgeon);
	}
	// end :: surgeons

	std::vector<std::unordered_map<std::string, SurgeonOTInfo>> surgeonsOTInfo;

	std::vector<Patient> patients;
	patients.reserve(problemData.getPatients().size());

	std::vector<std::vector<Assignment>> assignments;
	assignments.reserve(problemData.getNurses().size());
	
	std::priority_queue<PatientWrapper> patientQueue;
	std::vector<std::priority_queue<RoomWrapper>> roomsPerDays;
	roomsPerDays.reserve(days);
	
	for (const auto& patient : problemData.getPatients())
	{
		patientQueue.push(PatientWrapper(patient, problemData));
	}

	for (int i = 0; i < days; ++i)
	{
		std::priority_queue<RoomWrapper> queue;

		for (const auto& [id, room] : preprocessedRooms.at(i))
		{
			queue.push(RoomWrapper(room, problemData, id));
		}

		roomsPerDays.push_back(queue);
	}

	return CIndividual();
}

void GreedySolver::bestNextMove(CIndividual& individual)
{

}

std::pair<int, std::string> GreedySolver::chooseAdmissionDayAndOt(
	const IncomingPatientDTO& patient, 
	std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
	std::unordered_map<std::string, SurgeryTimeActualToMax>& surgeons
)
{
	for (int i = patient.getSurgeryReleaseDay(); i < patient.getSurgeryDueDay() && i < problemData.getDays(); ++i)
	{
		if (surgeons.at(patient.getSurgeonId()).max.at(i) >= patient.getSurgeryDuration())
		{
			for (auto& ot : operatingTheaters.at(i))
			{
				auto& operatingTheater = ot.operatingTheater;

				if (operatingTheater.max >= patient.getSurgeryDuration())
				{
					surgeons.at(patient.getSurgeonId()).current.at(i) += patient.getSurgeryDuration();
					operatingTheater.current += patient.getSurgeryDuration();

					std::make_heap(operatingTheaters.at(i).begin(), operatingTheaters.at(i).begin());

					return std::make_pair(i, operatingTheater.id);
				}
			}
		}
	}

	return std::make_pair(problemData.getDays(), "");
}

std::string GreedySolver::chooseRoomId(CIndividual& individual)
{
	return std::string();
}
