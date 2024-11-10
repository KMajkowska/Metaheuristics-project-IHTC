#include "GreedySolver.h"
#include <iostream>

GreedySolver::GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator) :
	IHTCSolver(problemData, randGenerator)
{}

CIndividual GreedySolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	const auto& shiftTypes = problemData.getShiftTypes();

	std::vector<Patient> patients;
	patients.reserve(problemData.getPatients().size());

	std::unordered_map<std::string, std::vector<Assignment>> assignments;
	assignments.reserve(problemData.getNurses().size());

	for (const auto& nurse : problemData.getNurses())
	{
		std::vector<Assignment> sol;

		for (const auto& shift : nurse.getWorkingShifts())
		{
			sol.push_back(Assignment(shift.getDay(), shift.getShift()));
		}

		assignments[nurse.getId()] = sol;
	}

	int days = problemData.getDays();

	RoomWithOccupancyRepresentation roomWithOccupancy = problemData.getPreprocessedRooms();
	ShiftNurses shiftNurses(problemData);

	// begin :: ots
	std::vector<std::vector<OperatingTheaterWrapper>> operatingTheaters = problemData.getOperatingTheatersAvailability();

	for (int i = 0; i < days; ++i)
	{
		std::sort(operatingTheaters[i].begin(), operatingTheaters[i].end(), std::greater<OperatingTheaterWrapper>());
	}
	// end :: ots

	// begin :: surgeonWorkloads
	std::unordered_map<std::string, Workload> surgeonWorkloads;
	surgeonWorkloads.reserve(problemData.getSurgeons().size());

	for (const auto& surgeon : problemData.getSurgeons())
	{
		surgeonWorkloads[surgeon.getId()] = Workload(surgeon);
	}
	// end :: surgeonWorkloads

	// begin :: nurseWorkloads
	std::unordered_map<std::string, Workload> nurseWorkloads;
	nurseWorkloads.reserve(problemData.getNurses().size());

	for (const auto& nurse : problemData.getNurses())
	{
		nurseWorkloads[nurse.getId()] = Workload(nurse, days, problemData.getShiftTypeToIndexMap());
	}
	// end :: nurseWorkloads

	std::priority_queue<PatientWrapper> patientQueue;

	for (const auto& patient : problemData.getPatients())
	{
		patientQueue.push(PatientWrapper(patient));
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
			&& dissallowedAdmissionDays.size() + patient.getSurgeryReleaseDay() < days // some patients have length of stay over our schedulign period (like i10, p0140)
			)
		{
			auto pair = chooseAdmissionDayAndOt(patient, operatingTheaters, surgeonWorkloads, dissallowedAdmissionDays);

			auto newAdmissionDay = pair.first;
			auto newOt = pair.second;
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

			std::cout << "ID: " << patient.getId() <<
				" ROOM: " << roomId <<
				" OT: " << ot <<
				" ADMISSION: " << admissionDay <<
				" D.A.D: " << dissallowedAdmissionDays.size() <<
				std::endl;
		}

		patients.push_back(Patient(patient.getId(), admissionDay, roomId, ot));

		roomWithOccupancy.addIncomingPatient(admissionDay, roomId, patient);

		patientQueue.pop();
	}


	for (const auto& room : problemData.getRooms())
	{
		std::vector<std::string> chosenNurses = chooseNurse(
			nurseWorkloads,
			shiftNurses,
			roomWithOccupancy,
			problemData.getNurses(),
			room.getId()
		);

		for (int i = 0; i < chosenNurses.size(); ++i)
		{
			if (chosenNurses[i].empty())
			{
				continue;
			}

			auto& assignment = assignments.at(chosenNurses[i]);
			int day = i / shiftTypes.size();
			int shiftOffset = i % shiftTypes.size();
			std::string shiftName = shiftTypes.at(shiftOffset);

			auto it = std::find_if(assignment.begin(), assignment.end(), [shiftName, day](const Assignment& assignment)
				{
					return assignment.getDay() == day && assignment.getShift() == shiftName;
				}
			);

			if (it == assignment.end())
			{
				throw std::exception("Invalid assignment");
			}

			assignment.at(it - assignment.begin()).appendRoom(room.getId());
		}
	}

	return CIndividual(patients, assignments);
}

std::vector<std::string> GreedySolver::chooseNurse(
	std::unordered_map<std::string, Workload>& nurseWorkloads,
	ShiftNurses& shiftNurses,
	RoomWithOccupancyRepresentation& roomWithOccupancy,
	const std::vector<NurseDTO> nurses,
	const std::string& roomId
) const
{
	std::vector<std::string> nursesPerShiftAndDayToRoom;
	nursesPerShiftAndDayToRoom.reserve(problemData.getDays() * problemData.getShiftTypes().size());

	for (size_t i = 0; i < problemData.getDays() * problemData.getShiftTypes().size(); ++i)
	{
		std::priority_queue<NurseWrapper> nursePrio;

		const int day = i / problemData.getShiftTypes().size();
		const int shiftOffset = i % problemData.getShiftTypes().size();

		const auto& room = roomWithOccupancy.getPatientRoomInfoRef(day, roomId);
		const auto& nurses = shiftNurses.getNursesByDayShiftOffset(i);

		const std::string shiftType = problemData.getShiftTypes().at(shiftOffset);

		auto it = room.skillLevelsRequired.find(shiftType);

		// room doesn't have any patient to take care of during this moment
		if (it == room.skillLevelsRequired.end())
		{
			nursesPerShiftAndDayToRoom.push_back("");
			continue;
		}

		for (const auto& nurse : nurses)
		{
			int currentSkillLevelsOverload = 0;
			int currWorkloadOverload = 0;

			for (const int skillLevel : it->second)
			{
				if (skillLevel > nurse.getSkillLevel())
				{
					currentSkillLevelsOverload += skillLevel - nurse.getSkillLevel();
				}
			}

			const auto& nurseWorkload = nurseWorkloads.at(nurse.getId());

			const auto& actualWorkload = room.shiftNameToProducedWorkload.at(shiftType);
			const auto& nurseWorkloadLefover = nurseWorkload.max.at(i) - nurseWorkload.current.at(i);

			if (actualWorkload > nurseWorkloadLefover)
			{
				currWorkloadOverload += actualWorkload - nurseWorkloadLefover;
			}

			// any other ?

			nursePrio.push(NurseWrapper(problemData.getWeights(), nurse, day, shiftType));
		}

		const auto& topNurse = nursePrio.top();

		nurseWorkloads.at(topNurse.nurse.getId()).current[i] += room.shiftNameToProducedWorkload.at(shiftType);

		nursesPerShiftAndDayToRoom.push_back(topNurse.nurse.getId());
	}

	return nursesPerShiftAndDayToRoom;
}

std::pair<int, std::string> GreedySolver::chooseAdmissionDayAndOt(
	const IncomingPatientDTO& patient,
	std::vector<std::vector<OperatingTheaterWrapper>>& operatingTheaters,
	std::unordered_map<std::string, Workload>& surgeons,
	std::vector<int>& disallowedAdmissionDays
) const
{
	for (int i = patient.getSurgeryReleaseDay(); i <= patient.getSurgeryDueDay() && i < problemData.getDays(); ++i)
	{
		auto it = std::find(disallowedAdmissionDays.begin(), disallowedAdmissionDays.end(), i);

		if (it != disallowedAdmissionDays.end())
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

	const auto& incompatibleRooms = patient.getIncompatibleRoomIds();

	for (const auto& room : problemData.getRooms())
	{
		auto it = std::find(incompatibleRooms.begin(), incompatibleRooms.end(), room.getId());

		if (it != incompatibleRooms.end())
		{
			continue;
		}

		// add 1 for each day that these are broken
		int brokenGender = 0;
		int brokenAgeGroup = 0;
		int brokenCapacity = 0;

		for (int i = admissionDay; i < patient.getLengthOfStay() + admissionDay && i < problemData.getDays(); ++i)
		{
			const auto& patientWorkload = patient.getWorkloadProduced().at(i - admissionDay);
			const auto& preprocessedRoom = roomWithOccupancy.getPatientRoomInfoRef(i, room.getId());

			if (preprocessedRoom.currentCapacity < patientWorkload)
			{
				brokenCapacity = patientWorkload - preprocessedRoom.currentCapacity;
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
		}

		roomPrioQueue.push(RoomBrokenAgeGender(brokenAgeGroup, brokenGender, brokenCapacity, room.getId()));
	}

	if (roomPrioQueue.empty())
	{
		return "";
	}

	return roomPrioQueue.top().id;
}
