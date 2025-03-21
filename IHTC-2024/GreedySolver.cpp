#include "GreedySolver.h"

GreedySolver::GreedySolver(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
	IHTCSolver(problemData, randGenerator, consumer)
{}

CIndividual GreedySolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
	const auto& shiftTypes { _problemData.shiftTypes() };

	std::vector<Patient> patients;
	patients.reserve(_problemData.patients().size());

	std::unordered_map<std::string, std::vector<Assignment>> assignments;
	assignments.reserve(_problemData.nurses().size());

	for (const auto& nurse : _problemData.nurses())
	{
		std::vector<Assignment> sol;

		for (const auto& shift : nurse.workingShifts())
		{
			sol.push_back(Assignment(shift.day(), shift.shift()));
		}

		assignments[nurse.id()] = sol;
	}

	auto days { _problemData.days() };

	RoomWithOccupancyRepresentation roomWithOccupancy { _problemData.getPreprocessedRooms() };
	ShiftNurses shiftNurses(_problemData);

	// begin :: ots
	std::vector<std::vector<OperatingTheaterWrapper>> operatingTheaters { _problemData.operatingTheatersAvailability() };

	for (int i = 0; i < days; ++i)
	{
		std::sort(operatingTheaters[i].begin(), operatingTheaters[i].end(), std::greater<OperatingTheaterWrapper>());
	}
	// end :: ots

	// begin :: surgeonWorkloads
	std::unordered_map<std::string, Workload> surgeonWorkloads;
	surgeonWorkloads.reserve(_problemData.surgeons().size());

	for (const auto& surgeon : _problemData.surgeons())
	{
		surgeonWorkloads[surgeon.id()] = Workload(surgeon);
	}
	// end :: surgeonWorkloads

	// begin :: nurseWorkloads
	std::unordered_map<std::string, Workload> nurseWorkloads;
	nurseWorkloads.reserve(_problemData.nurses().size());

	for (const auto& nurse : _problemData.nurses())
	{
		nurseWorkloads[nurse.id()] = Workload(nurse, days, _problemData.getShiftTypeToIndexMap());
	}
	// end :: nurseWorkloads

	std::priority_queue<PatientWrapper> patientQueue;

	for (const auto& patient : _problemData.patients())
	{
		patientQueue.push(PatientWrapper(patient));
	}

	while (!patientQueue.empty())
	{
		const auto& patientWrapper { patientQueue.top() };
		const auto& patient { patientWrapper.patient() };

		auto admissionDay { _problemData.days() };
		std::string ot { "" };
		std::string roomId { "" };

		std::vector<int> dissallowedAdmissionDays;

		while (
			admissionDay >= _problemData.days()
			&& roomId.empty()
			&& ot.empty()
			&& dissallowedAdmissionDays.size() < patient.lengthOfStay()
			&& dissallowedAdmissionDays.size() + patient.getSurgeryReleaseDay() < days // some patients have length of stay over our schedulign period (like i10, p0140)
			)
		{
			auto pair = chooseAdmissionDayAndOt(patient, operatingTheaters, surgeonWorkloads, dissallowedAdmissionDays);

			auto newAdmissionDay { pair.first };
			auto newOt { pair.second };
			auto newRoomId { chooseRoomId(patient, roomWithOccupancy, newAdmissionDay) };

			if (newAdmissionDay < _problemData.days())
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

		patients.push_back(Patient(patient.id(), admissionDay, roomId, ot));

		roomWithOccupancy.addIncomingPatient(admissionDay, roomId, patient);

		patientQueue.pop();
	}

	for (const auto& room : _problemData.rooms())
	{
		std::vector<std::string> chosenNurses
		{
			chooseNurse(
				nurseWorkloads,
				shiftNurses,
				roomWithOccupancy,
				_problemData.nurses(),
				room.id()
			)
		};

		for (size_t i = 0; i < chosenNurses.size(); ++i)
		{
			if (chosenNurses[i].empty())
			{
				continue;
			}

			auto& assignment { assignments.at(chosenNurses[i]) };
			auto day { i / shiftTypes.size() };
			auto shiftOffset { i % shiftTypes.size() };
			std::string shiftName{ shiftTypes.at(shiftOffset) };

			auto it
			{
				std::find_if(
					assignment.begin(), assignment.end(), [shiftName, day](const Assignment& assignment)
					{
						return assignment.day() == day && assignment.shift() == shiftName;
					}
				)
			};

			if (it == assignment.end())
			{
				throw std::exception("Invalid assignment");
			}

			assignment.at(it - assignment.begin()).appendRoom(room.id());
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
	nursesPerShiftAndDayToRoom.reserve(_problemData.days() * _problemData.shiftTypes().size());

	for (size_t i = 0; i < _problemData.days() * _problemData.shiftTypes().size(); ++i)
	{
		std::priority_queue<NurseWrapper> nursePrio;

		const auto day { i / _problemData.shiftTypes().size() };
		const auto shiftOffset { i % _problemData.shiftTypes().size() };

		const auto& room { roomWithOccupancy.patientRoomInfoRef(day, roomId) };
		const auto& nurses { shiftNurses.getNursesByDayShiftOffset(i) };

		const std::string shiftType { _problemData.shiftTypes().at(shiftOffset) };

		auto it { room._skillLevelsRequired.find(shiftType) };

		// room doesn't have any patient to take care of during this moment
		if (it == room._skillLevelsRequired.end())
		{
			nursesPerShiftAndDayToRoom.push_back("");
			continue;
		}

		for (const auto& nurse : nurses)
		{
			int currentSkillLevelsOverload { 0 };
			int currWorkloadOverload { 0 };

			for (const int skillLevel : it->second)
			{
				if (skillLevel > nurse.skillLevel())
				{
					currentSkillLevelsOverload += skillLevel - nurse.skillLevel();
				}
			}

			auto& nurseWorkload { nurseWorkloads.at(nurse.id()) };

			const auto& actualWorkload { room._shiftNameToProducedWorkload.at(shiftType) };
			const auto& nurseWorkloadLefover { nurseWorkload.max().at(i) - nurseWorkload.current().at(i) };

			if (actualWorkload > nurseWorkloadLefover)
			{
				currWorkloadOverload += actualWorkload - nurseWorkloadLefover;
			}

			// any other ?

			nursePrio.push(NurseWrapper(_problemData.weights(), nurse, day, shiftType));
		}

		const auto& topNurse { nursePrio.top() };

		nurseWorkloads.at(topNurse.nurse().id()).current()[i] += room._shiftNameToProducedWorkload.at(shiftType);

		nursesPerShiftAndDayToRoom.push_back(topNurse.nurse().id());
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
	for (int i = patient.getSurgeryReleaseDay(); i <= patient.getSurgeryDueDay() && i < _problemData.days(); ++i)
	{
		auto it{ std::find(disallowedAdmissionDays.begin(), disallowedAdmissionDays.end(), i) };

		if (it != disallowedAdmissionDays.end())
		{
			continue;
		}

		if (surgeons.at(patient.getSurgeonId()).max().at(i) - surgeons.at(patient.getSurgeonId()).current().at(i) < patient.getSurgeryDuration())
		{
			disallowedAdmissionDays.push_back(i);
			continue;
		}

		for (auto& ot : operatingTheaters.at(i))
		{
			auto& operatingTheater { ot.operatingTheater() };

			if (operatingTheater.max() - operatingTheater.current() >= patient.getSurgeryDuration())
			{
				surgeons.at(patient.getSurgeonId()).current().at(i) += patient.getSurgeryDuration();
				operatingTheater.setCurrent(operatingTheater.current() + patient.getSurgeryDuration());

				std::sort(operatingTheaters.at(i).begin(), operatingTheaters.at(i).begin(), std::greater<OperatingTheaterWrapper>());

				return std::make_pair(i, operatingTheater.id());
			}
		}

		disallowedAdmissionDays.push_back(i);
	}

	return std::make_pair(_problemData.days(), "");
}

std::string GreedySolver::chooseRoomId(
	const IncomingPatientDTO& patient,
	RoomWithOccupancyRepresentation& roomWithOccupancy,
	int admissionDay
) const
{
	if (admissionDay >= _problemData.days())
	{
		return "";
	}

	const auto& weight = _problemData.weights();

	std::priority_queue<RoomBrokenAgeGender> roomPrioQueue;

	const auto& incompatibleRooms = patient.getIncompatibleRoomIds();

	for (const auto& room : _problemData.rooms())
	{
		auto it { std::find(incompatibleRooms.begin(), incompatibleRooms.end(), room.id()) };

		if (it != incompatibleRooms.end())
		{
			continue;
		}

		// add 1 for each day that these are broken
		int brokenGender { 0 };
		int brokenAgeGroup { 0 };
		int brokenCapacity { 0 };

		for (int i = admissionDay; i < patient.lengthOfStay() + admissionDay && i < _problemData.days(); ++i)
		{
			const auto& preprocessedRoom { roomWithOccupancy.patientRoomInfoRef(i, room.id()) };

			if (preprocessedRoom._currentCapacity > 0)
			{
				++brokenCapacity;
			}

			for (const auto& [gender, _] : preprocessedRoom._genders)
			{
				if (gender != patient.gender())
				{
					++brokenGender;
					break;
				}
			}

			for (const auto& [ageGroup, _] : preprocessedRoom._ageGroups)
			{
				if (ageGroup != patient.ageGroup())
				{
					++brokenAgeGroup;
					break;
				}
			}
		}

		roomPrioQueue.push(RoomBrokenAgeGender(brokenAgeGroup, brokenGender, brokenCapacity, room.id()));
	}

	if (roomPrioQueue.empty())
	{
		return "";
	}

	return roomPrioQueue.top().id();
}
