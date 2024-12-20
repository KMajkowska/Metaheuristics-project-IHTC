#include "solutionUtils.h"
#include "params.h"

ViolatedRestrictions getViolatedFromSolution(const ProblemData& problemData, const SolutionData& solution)
{

	const auto& days = problemData.getDays();
	const auto& allShiftTypes = problemData.getShiftTypes();
	const auto& operationTheathers = problemData.getOperatingTheaters();
	const auto& problemSurgeons = problemData.getSurgeons();

	ViolatedRestrictions res;
	RoomWithOccupancyRepresentation roomInfos = problemData.getPreprocessedRooms();
	PatientNurses patientNurses(problemData);

	std::vector<std::unordered_map<std::string, SurgeonOTInfo>> surgeonsOTInfo;
	std::vector<std::unordered_map<std::string, std::set<std::string>>> surgeonToOTPerDay;
	std::unordered_map<std::string, NurseWorkload> nurseIdsToWorloads;
	std::vector<std::set<std::string>> openOTs(days);

	surgeonsOTInfo.reserve(days);
	surgeonToOTPerDay.reserve(days);
	nurseIdsToWorloads.reserve(problemData.getNurses().size());

	for (const auto& nurse : problemData.getNurses())
	{
		NurseWorkload res(std::vector<int>(days * allShiftTypes.size(), 0), std::vector<int>(days * allShiftTypes.size(), 0));

		for (const auto& workingShift : nurse.getWorkingShifts())
		{
			res.maximumWorkload[workingShift.getDay() * allShiftTypes.size() + problemData.getOffsetOfShiftTypes(workingShift.getShift())] = workingShift.getMaxLoad();
		}

		nurseIdsToWorloads[nurse.getId()] = res;
	}

	for (const auto& nurse : solution.getNurses())
	{
		roomInfos.addNurse(nurse);
	}

	for (const auto& solutionPatients : solution.getPatients())
	{
		int admissionDay = solutionPatients.getAdmissionDay();
		const auto patient = problemData.getPatientMap().at(solutionPatients.getId());

		roomInfos.addIncomingPatient(admissionDay, solutionPatients.getRoomId(), patient);

		for (int i = 0; i < patient.getLengthOfStay() && i + admissionDay < days && !solutionPatients.getRoomId().empty(); ++i)
		{
			const auto& roomRef = roomInfos.getPatientRoomInfoRef(i + admissionDay, solutionPatients.getRoomId());

			for (const auto& [nurseId, shift] : roomRef.nurseIdToShift)
			{
				patientNurses.addNurse(patient.getId(), nurseId);
			}
		}
	}

	for (int i = 0; i < days; i++)
	{
		std::unordered_map<std::string, SurgeonOTInfo> operatingTheaterWorkingTime;
		operatingTheaterWorkingTime.reserve(days);

		for (const auto& OT : operationTheathers)
		{
			operatingTheaterWorkingTime[OT.getId()] = SurgeonOTInfo(OT.getAvailability()[i]);
		}

		surgeonsOTInfo.push_back(operatingTheaterWorkingTime);
	}

	for (const auto& solutionPatient : solution.getPatients())
	{
		const auto& admissionDay = solutionPatient.getAdmissionDay();
		if (admissionDay < openOTs.size())
		{
			const auto patient = problemData.getPatientMap().at(solutionPatient.getId());
			const auto& operatingTheater = solutionPatient.getOperationTheater();
			const auto surgeon = problemData.getSurgeonMap()[patient.getSurgeonId()];

			openOTs[solutionPatient.getAdmissionDay()].insert(solutionPatient.getOperationTheater());

			auto& workingTime = surgeonsOTInfo[admissionDay][operatingTheater].surgeonsOperations[surgeon.getId()];

			workingTime.actualWorkingTime += patient.getSurgeryDuration();
			workingTime.maxSurgeonCapacity = surgeon.getMaxSurgeryTime()[admissionDay];
		}
	}

	for (int i = 0; i < days; i++)
	{
		for (const auto& [id, roomValue] : roomInfos.getRoomsForGivenDayRef(i))
		{
			for (const auto& occupantId : roomValue.occupantIds)
			{
				for (const auto& [nurseId, shift] : roomValue.nurseIdToShift)
				{
					patientNurses.addNurse(occupantId, nurseId);
				}
			}

			if (roomValue.genders.size() > 1)
			{
				++res.countGenderMixHard;
			}

			if (roomValue.currentCapacity < 0)
			{
				++res.countOvercrowdedCapacityHard;
			}

			if (roomValue.ageGroups.size() > 1)
			{
				++res.countMixedAgeGroups;
			}

			for (const auto& patient : roomValue.patientIds)
			{
				const auto& isPatient = std::find(roomValue.unallowedPatients.begin(), roomValue.unallowedPatients.end(), patient);

				if (isPatient != roomValue.unallowedPatients.end())
				{
					res.countIncompatibleRoomsHard++;
				}
			}

			if (roomValue.patientIds.size() > 0 && roomValue.shiftToNurseId.size() < allShiftTypes.size())
			{
				res.countUncoveredRoomHard += allShiftTypes.size() - roomValue.shiftToNurseId.size();
			}

			for (const auto& shiftPair : roomValue.shiftToNurseId)
			{
				const auto nurseSkillLevel = problemData.getNursesMap()[shiftPair.second].getSkillLevel();

				auto it = roomValue.skillLevelsRequired.find(shiftPair.first);

				if (it != roomValue.skillLevelsRequired.end())
				{
					for (const auto& reqSkillLevel : it->second)
					{
						if (reqSkillLevel > nurseSkillLevel)
						{
							res.countMinimumSkillLevelExceeded += reqSkillLevel - nurseSkillLevel;
						}
					}
				}
			}

			for (const auto& shiftWorkloadPair : roomValue.shiftNameToProducedWorkload)
			{
				auto it = roomValue.shiftToNurseId.find(shiftWorkloadPair.first);

				if (it != roomValue.shiftToNurseId.end())
				{
					const auto nurse = problemData.getNursesMap()[it->second];
					const auto& nurseWorkload = nurse.getWorkloadByDayAndShift(i, it->first);

					const int idx = i * problemData.getShiftTypes().size() + problemData.getOffsetOfShiftTypes(it->first);

					nurseIdsToWorloads[nurse.getId()].actualWorkload[idx] += shiftWorkloadPair.second;
				}
			}

			for (const auto& nurse : problemData.getNurses())
			{
				auto it = roomValue.nurseIdToShift.find(nurse.getId());
				bool isNurseFound = it != roomValue.nurseIdToShift.end();

				if (isNurseFound && nurse.getWorkloadByDayAndShift(i, it->second) <= 0)
				{
					++res.countNursePresentOnWrongDayHard;
				}
			}
		}
	}

	for (const auto& nurse : nurseIdsToWorloads)
	{
		for (int i = 0; i < nurse.second.actualWorkload.size(); ++i)
		{
			if (nurse.second.actualWorkload[i] > nurse.second.maximumWorkload[i])
			{
				res.countMaximumWorkloadExcceeded += nurse.second.actualWorkload[i] - nurse.second.maximumWorkload[i];
			}
		}
	}

	for (const auto& patient : solution.getPatients())
	{
		const auto patientFromProblem = problemData.getPatientMap().at(patient.getId());

		if (patient.getAdmissionDay() < 0 || patient.getAdmissionDay() >= days)
		{
			if (patientFromProblem.getSurgeryDueDay() <= days)
			{
				res.countUnadmittedMandatoryHard++;
			}
			else
			{
				res.countUncheduledOptional++;
			}
		}
		else if (patient.getAdmissionDay() > patientFromProblem.getSurgeryDueDay())
		{
			res.countLateAdmittedMandatoryHard++;
		}
		else if (patient.getAdmissionDay() > patientFromProblem.getSurgeryReleaseDay())
		{
			res.countAdmissionDelay += patient.getAdmissionDay() - patientFromProblem.getSurgeryReleaseDay();
		}
	}

	for (int i = 0; i < surgeonsOTInfo.size(); ++i)
	{
		std::unordered_map<std::string, std::set<std::string>> surgeonsToOTs;
		surgeonsToOTs.reserve(problemSurgeons.size());

		for (const auto& pair : surgeonsOTInfo[i])
		{
			if (pair.second.isOTOvercrowded())
			{
				++res.countOTOvertimeHard;
			}
		}

		for (const auto& surgeon : problemSurgeons)
		{
			int summedUpWorkingTime = 0;

			for (const auto& pair : surgeonsOTInfo[i])
			{
				const auto& ot = pair.second;
				const auto& it = ot.surgeonsOperations.find(surgeon.getId());

				if (it != ot.surgeonsOperations.end())
				{
					summedUpWorkingTime += it->second.actualWorkingTime;
				}

				surgeonsToOTs[surgeon.getId()].insert(pair.first);
			}

			if (surgeon.getMaxSurgeryTime()[i] < summedUpWorkingTime)
			{
				++res.countSurgeonOvertimeHard;
			}
		}

		surgeonToOTPerDay.push_back(surgeonsToOTs);
	}

	for (const auto& patientToNurse : patientNurses.getMap())
	{
		res.countUncontinuousCare += patientToNurse.second.size();
	}

	for (const auto& day : surgeonToOTPerDay)
	{
		for (const auto& pair : day)
		{
			if (pair.second.size() > 1)
			{
				++res.countSurgeonTransfer;
			}
		}
	}

	for (auto const& days : openOTs)
	{
		res.countOpenOTs += days.size();
	}

	return res;
}

double calculateFitness(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions)
{
	int maxWeight = weights.getMaxWeight() * hRestrictionModifier;

	return restrictions.countGenderMixHard * maxWeight
		+ restrictions.countIncompatibleRoomsHard * maxWeight
		+ restrictions.countOvercrowdedCapacityHard * maxWeight
		+ restrictions.countUnadmittedMandatoryHard * maxWeight
		+ restrictions.countLateAdmittedMandatoryHard * maxWeight
		+ restrictions.countSurgeonOvertimeHard * maxWeight
		+ restrictions.countOTOvertimeHard * maxWeight
		+ restrictions.countUncoveredRoomHard * maxWeight
		+ restrictions.countNursePresentOnWrongDayHard * maxWeight
		+ restrictions.countMixedAgeGroups * weights.getRoomMixedAge()
		+ restrictions.countMinimumSkillLevelExceeded * weights.getRoomNurseSkill()
		+ restrictions.countUncontinuousCare * weights.getContinuityOfCare()
		+ restrictions.countMaximumWorkloadExcceeded * weights.getNurseEccessiveWorkload()
		+ restrictions.countOpenOTs * weights.getOpenOperatingTheater()
		+ restrictions.countSurgeonTransfer * weights.getSurgeonTransfer()
		+ restrictions.countAdmissionDelay * weights.getPatientDelay()
		+ restrictions.countUncheduledOptional * weights.getUnscheduledOptional();
}

std::vector<std::pair<double, ViolatedRestrictions>> evaluateProblem(int amountOfRepetitions, const IProblem& problem, const ISolver& solver, const ISolver& initializeSolver)
{
	std::vector<std::pair<double, ViolatedRestrictions>> fitnesses;
	fitnesses.reserve(amountOfRepetitions);

	for (int i = 0; i < amountOfRepetitions; ++i)
	{
		CIndividual startingIndividual = initializeSolver.solve(problem, CIndividual());

		const CIndividual& individual = solver.solve(problem, startingIndividual);

		fitnesses.push_back(
			individual.isFitnessUpToDate()
			? individual.getFitness()
			: problem.eval(individual)
		);
	}

	return fitnesses;
}