#include "solutionUtils.h"
#include "params.h"

ViolatedRestrictions getViolatedFromSolution(const ProblemData& problemData, const SolutionData& solution)
{

	const auto& days { problemData.days() };
	const auto& allShiftTypes { problemData.shiftTypes() };
	const auto& operationTheathers { problemData.operatingTheaters() };
	const auto& problemSurgeons { problemData.surgeons() };

	ViolatedRestrictions res;
	RoomWithOccupancyRepresentation roomInfos { problemData.getPreprocessedRooms() };
	PatientNurses patientNurses(problemData);

	std::vector<std::unordered_map<std::string, SurgeonOTInfo>> surgeonsOTInfo;
	std::vector<std::unordered_map<std::string, std::set<std::string>>> surgeonToOTPerDay;
	std::unordered_map<std::string, NurseWorkload> nurseIdsToWorloads;
	std::vector<std::set<std::string>> openOTs(days);

	surgeonsOTInfo.reserve(days);
	surgeonToOTPerDay.reserve(days);
	nurseIdsToWorloads.reserve(problemData.nurses().size());

	for (const auto& nurse : problemData.nurses())
	{
		NurseWorkload res(std::vector<int>(days * allShiftTypes.size(), 0), std::vector<int>(days * allShiftTypes.size(), 0));

		for (const auto& workingShift : nurse.workingShifts())
		{
			res.maximumWorkload()[workingShift.day() * allShiftTypes.size() + problemData.getOffsetOfShiftTypes(workingShift.shift())] = workingShift.maxLoad();
		}

		nurseIdsToWorloads[nurse.id()] = res;
	}

	for (const auto& nurse : solution.nurses())
	{
		roomInfos.addNurse(nurse);
	}

	for (const auto& solutionPatients : solution.patients())
	{
		int admissionDay = solutionPatients.admissionDay();
		const auto patient = problemData.getPatientMap().at(solutionPatients.id());

		roomInfos.addIncomingPatient(admissionDay, solutionPatients.roomId(), patient);

		for (int i = 0; i < patient.lengthOfStay() && i + admissionDay < days && !solutionPatients.roomId().empty(); ++i)
		{
			auto& roomRef { roomInfos.patientRoomInfoRef(i + admissionDay, solutionPatients.roomId()) };

			for (const auto& [nurseId, shift] : roomRef.nurseIdToShift())
			{
				patientNurses.addNurse(patient.id(), nurseId);
			}
		}
	}

	for (int i = 0; i < days; i++)
	{
		std::unordered_map<std::string, SurgeonOTInfo> operatingTheaterWorkingTime;
		operatingTheaterWorkingTime.reserve(days);

		for (const auto& OT : operationTheathers)
		{
			operatingTheaterWorkingTime[OT.id()] = SurgeonOTInfo(OT.getAvailability()[i]);
		}

		surgeonsOTInfo.push_back(operatingTheaterWorkingTime);
	}

	for (const auto& solutionPatient : solution.patients())
	{
		const auto& admissionDay { solutionPatient.admissionDay() };

		if (admissionDay < openOTs.size())
		{
			const auto patient { problemData.getPatientMap().at(solutionPatient.id()) };
			const auto& operatingTheater { solutionPatient.operationTheater() };
			const auto surgeon { problemData.getSurgeonMap()[patient.getSurgeonId()] };

			openOTs[solutionPatient.admissionDay()].insert(solutionPatient.operationTheater());

			auto& workingTime = surgeonsOTInfo[admissionDay][operatingTheater].surgeonsOperations()[surgeon.id()];

			workingTime.setActualWorkingTime(workingTime.actualWorkingTime() + patient.getSurgeryDuration());
			workingTime.setMaxSurgeonCapacity(workingTime.maxSurgeonCapacity() + surgeon.maxSurgeryTime()[admissionDay]);
		}
	}

	for (size_t i { 0 }; i < days; ++i)
	{
		for (auto& [id, roomValue] : roomInfos.roomsForGivenDayRef(i))
		{
			for (const auto& occupantId : roomValue.occupantIds)
			{
				for (const auto& [nurseId, shift] : roomValue.nurseIdToShift())
				{
					patientNurses.addNurse(occupantId, nurseId);
				}
			}

			if (roomValue.genders.size() > 1)
			{
				res.setCountGenderMixHard();
			}

			if (roomValue.currentCapacity < 0)
			{
				res.countOvercrowdedCapacityHard();
			}

			if (roomValue.ageGroups.size() > 1)
			{
				res.countMixedAgeGroups();
			}

			for (const auto& patient : roomValue.patientIds())
			{
				const auto& isPatient { std::find(roomValue.unallowedPatients.begin(), roomValue.unallowedPatients.end(), patient) };

				if (isPatient != roomValue.unallowedPatients.end())
				{
					res.setCountIncompatibleRoomsHard();
				}
			}

			if (roomValue.patientIds().size() > 0 && roomValue.shiftToNurseId().size() < allShiftTypes.size())
			{
				res.setCountUncoveredRoomHard(allShiftTypes.size() - roomValue.shiftToNurseId().size());
			}

			for (const auto& shiftPair : roomValue.shiftToNurseId())
			{
				const auto nurseSkillLevel { problemData.getNursesMap()[shiftPair.second].skillLevel() };

				auto it { roomValue.skillLevelsRequired.find(shiftPair.first) };

				if (it != roomValue.skillLevelsRequired.end())
				{
					for (const auto& reqSkillLevel : it->second)
					{
						if (reqSkillLevel > nurseSkillLevel)
						{
							res.setCountMinimumSkillLevelExceeded(reqSkillLevel - nurseSkillLevel);
						}
					}
				}
			}

			for (const auto& shiftWorkloadPair : roomValue.shiftNameToProducedWorkload)
			{
				auto it { roomValue.shiftToNurseId().find(shiftWorkloadPair.first)};

				if (it != roomValue.shiftToNurseId().end())
				{
					const auto nurse { problemData.getNursesMap()[it->second] };
					const auto& nurseWorkload { nurse.getWorkloadByDayAndShift(i, it->first) };

					const auto idx { i * problemData.shiftTypes().size() + problemData.getOffsetOfShiftTypes(it->first) };

					nurseIdsToWorloads[nurse.id()].actualWorkload()[idx] += shiftWorkloadPair.second;
				}
			}

			for (const auto& nurse : problemData.nurses())
			{
				auto it { roomValue.nurseIdToShift().find(nurse.id())};
				bool isNurseFound { it != roomValue.nurseIdToShift().end()};

				if (isNurseFound && nurse.getWorkloadByDayAndShift(i, it->second) <= 0)
				{
					res.setCountNursePresentOnWrongDayHard();
				}
			}
		}
	}

	for (auto& nurse : nurseIdsToWorloads)
	{
		for (int i = 0; i < nurse.second.actualWorkload().size(); ++i)
		{
			if (nurse.second.actualWorkload()[i] > nurse.second.maximumWorkload()[i])
			{
				res.setCountMaximumWorkloadExcceeded(nurse.second.actualWorkload()[i] - nurse.second.maximumWorkload()[i]);
			}
		}
	}

	for (const auto& patient : solution.patients())
	{
		const auto patientFromProblem = problemData.getPatientMap().at(patient.id());

		if (patient.admissionDay() < 0 || patient.admissionDay() >= days)
		{
			if (patientFromProblem.getSurgeryDueDay() <= days)
			{
				res.setCountUnadmittedMandatoryHard();
			}
			else
			{
				res.setCountUncheduledOptional();
			}
		}
		else if (patient.admissionDay() > patientFromProblem.getSurgeryDueDay())
		{
			res.setCountLateAdmittedMandatoryHard();
		}
		else if (patient.admissionDay() > patientFromProblem.getSurgeryReleaseDay())
		{
			res.setCountAdmissionDelay(patient.admissionDay() - patientFromProblem.getSurgeryReleaseDay());
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
				res.setCountOTOvertimeHard();
			}
		}

		for (const auto& surgeon : problemSurgeons)
		{
			int summedUpWorkingTime = 0;

			for (auto& pair : surgeonsOTInfo[i])
			{
				auto& ot { pair.second };
				const auto& it { ot.surgeonsOperations().find(surgeon.id()) };

				if (it != ot.surgeonsOperations().end())
				{
					summedUpWorkingTime += it->second.actualWorkingTime();
				}

				surgeonsToOTs[surgeon.id()].insert(pair.first);
			}

			if (surgeon.maxSurgeryTime()[i] < summedUpWorkingTime)
			{
				res.setCountSurgeonOvertimeHard();
			}
		}

		surgeonToOTPerDay.push_back(surgeonsToOTs);
	}

	for (const auto& patientToNurse : patientNurses.occupantsAndPatientToNurses())
	{
		res.setCountUncontinuousCare(patientToNurse.second.size());
	}

	for (const auto& day : surgeonToOTPerDay)
	{
		for (const auto& pair : day)
		{
			if (pair.second.size() > 1)
			{
				res.setCountSurgeonTransfer();
			}
		}
	}

	for (auto const& days : openOTs)
	{
		res.setCountOpenOTs(days.size());
	}

	return res;
}

double calculateFitness(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions)
{
	auto maxWeight { weights.getMaxWeight() * hRestrictionModifier };

	return restrictions.countGenderMixHard() * maxWeight
		+ restrictions.countIncompatibleRoomsHard() * maxWeight
		+ restrictions.countOvercrowdedCapacityHard() * maxWeight
		+ restrictions.countUnadmittedMandatoryHard() * maxWeight
		+ restrictions.countLateAdmittedMandatoryHard() * maxWeight
		+ restrictions.countSurgeonOvertimeHard() * maxWeight
		+ restrictions.countOTOvertimeHard() * maxWeight
		+ restrictions.countUncoveredRoomHard() * maxWeight
		+ restrictions.countNursePresentOnWrongDayHard() * maxWeight
		+ restrictions.countMixedAgeGroups() * weights.getRoomMixedAge()
		+ restrictions.countMinimumSkillLevelExceeded() * weights.getRoomNurseSkill()
		+ restrictions.countUncontinuousCare() * weights.getContinuityOfCare()
		+ restrictions.countMaximumWorkloadExcceeded() * weights.getNurseEccessiveWorkload()
		+ restrictions.countOpenOTs() * weights.getOpenOperatingTheater()
		+ restrictions.countSurgeonTransfer() * weights.getSurgeonTransfer()
		+ restrictions.countAdmissionDelay() * weights.getPatientDelay()
		+ restrictions.countUncheduledOptional() * weights.getUnscheduledOptional();
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
			? individual.fitness()
			: problem.eval(individual)
		);
	}

	return fitnesses;
}