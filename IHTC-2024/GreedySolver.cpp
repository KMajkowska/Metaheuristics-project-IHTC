#include "GreedySolver.h"

GreedySolver::GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator) :
	IHTCSolver(problemData, randGenerator)
{}

CIndividual GreedySolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	std::vector<Patient> patients;
	patients.reserve(problemData.getPatients().size());

	std::vector<std::vector<Assignment>> assignments;
	assignments.reserve(problemData.getNurses().size());

	int days = problemData.getDays();

	RoomWithOccupancyRepresentation roomWithOccupancy = problemData.getPreprocessedRooms();
	ShiftNurses shiftNurses(problemData);
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

		std::sort(operatingTheaters[i].begin(), operatingTheaters[i].end(), std::greater<OperatingTheaterWrapper>());
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

	std::priority_queue<PatientWrapper> patientQueue;

	for (const auto& patient : problemData.getPatients())
	{
		patientQueue.push(PatientWrapper(patient, problemData));	
	}

	while (!patientQueue.empty())
	{
		const auto& patientWrapper = patientQueue.top();
		auto& patient = patientWrapper.patient;

		int admissionDay = problemData.getDays();
		std::string ot = "";
		std::string roomId = "";

		std::vector<int> dissallowedAdmissionDays;

		while (
			admissionDay >= problemData.getDays()
			&& roomId.empty()
			&& ot.empty()
			&& dissallowedAdmissionDays.size() < patient.getLengthOfStay()
			)
		{
			auto [newAdmissionDay, newOt] = chooseAdmissionDayAndOt(patient, operatingTheaters, surgeons, dissallowedAdmissionDays);

			auto newRoomId = chooseRoomId(patient, roomWithOccupancy, newAdmissionDay);

			if (newAdmissionDay < problemData.getDays())
			{
				admissionDay = newAdmissionDay;
			}

			if (!newOt.empty())
			{
				ot = newOt;
			}

			if (!newRoomId.empty())
			{
				roomId = newRoomId;
			}
		}

		patients.push_back(Patient(patient.getId(), admissionDay, roomId, ot));

		roomWithOccupancy.addIncomingPatient(admissionDay, roomId, patient);
	}

	return CIndividual(patients, assignments);
}

std::string GreedySolver::chooseNurse(
	ShiftNurses& shiftNurses, 
	RoomWithOccupancyRepresentation& roomWithOccupancy, 
	const std::vector<NurseDTO> nurses, 
	const std::string& roomId
) const
{
	for (int i = 0; i < problemData.getDays() * problemData.getShiftTypes().size(); ++i)
	{
		const auto& nurses = shiftNurses.getNursesByDayShiftOffset(i);
	}
}

std::pair<int, std::string> GreedySolver::chooseAdmissionDayAndOt(
	const IncomingPatientDTO& patient,
	std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
	std::unordered_map<std::string, SurgeryTimeActualToMax>& surgeons,
	std::vector<int>& disallowedAdmissionDays
) const
{
	for (int i = patient.getSurgeryReleaseDay(); i < patient.getSurgeryDueDay() && i < problemData.getDays(); ++i)
	{
		auto it = std::find(disallowedAdmissionDays.begin(), disallowedAdmissionDays.end(), i);

		if (it == disallowedAdmissionDays.end())
		{
			continue;
		}

		if (surgeons.at(patient.getSurgeonId()).max.at(i) - surgeons.at(patient.getSurgeonId()).current.at(i) < patient.getSurgeryDuration())
		{
			disallowedAdmissionDays.push_back(i);
			continue;
		}

		for (auto& ot : operatingTheaters.at(i))
		{
			auto& operatingTheater = ot.operatingTheater;

			if (operatingTheater.max - operatingTheater.current >= patient.getSurgeryDuration())
			{
				surgeons.at(patient.getSurgeonId()).current.at(i) += patient.getSurgeryDuration();
				operatingTheater.current += patient.getSurgeryDuration();

				std::sort(operatingTheaters.at(i).begin(), operatingTheaters.at(i).begin(), std::greater<OperatingTheaterWrapper>());

				return std::make_pair(i, operatingTheater.id);
			}
		}
		disallowedAdmissionDays.push_back(i);
	}

	return std::make_pair(problemData.getDays(), "");
}

std::string GreedySolver::chooseRoomId(
	const IncomingPatientDTO& patient,
	RoomWithOccupancyRepresentation& roomWithOccupancy,
	int admissionDay
) const
{
	if (admissionDay >= problemData.getDays())
	{
		return "";
	}

	const auto& weight = problemData.getWeights();
	std::priority_queue<RoomBrokenAgeGender> roomPrioQueue;

	for (const auto& room : problemData.getRooms())
	{
		auto it = std::find(patient.getIncompatibleRoomIds().begin(), patient.getIncompatibleRoomIds().end(), room.getId());

		if (it == patient.getIncompatibleRoomIds().end())
		{
			continue;
		}

		// add 1 for each day that these are broken
		int brokenGender = 0;
		int brokenAgeGroup = 0;

		bool hasSpaceForPatient = true;
		bool anyChecked = false;

		for (int i = admissionDay; i < patient.getLengthOfStay() + admissionDay && i < problemData.getDays() && hasSpaceForPatient; ++i)
		{
			const auto& preprocessedRoom = roomWithOccupancy.getPatientRoomInfoRef(i, room.getId());

			if (preprocessedRoom.currentCapacity <= 0)
			{
				hasSpaceForPatient = false;
			}

			for (const auto& [gender, _] : preprocessedRoom.genders)
			{
				if (gender != patient.getGender())
				{
					++brokenGender;
					break;
				}
			}

			for (const auto& [ageGroup, _] : preprocessedRoom.ageGroups)
			{
				if (ageGroup != patient.getAgeGroup())
				{
					++brokenAgeGroup;
					break;
				}
			}

			anyChecked = true;
		}

		if (hasSpaceForPatient && anyChecked)
		{
			roomPrioQueue.push(RoomBrokenAgeGender(brokenAgeGroup, brokenGender, room.getId()));
		}
	}

	if (roomPrioQueue.empty())
	{
		return "";
	}

	return roomPrioQueue.top().id;
}
