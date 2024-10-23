#include "solutionUtils.h"

ViolatedRestrictions getViolatedFromSolution(ProblemData& problemData, const SolutionData& solution)
{
    ViolatedRestrictions res;
	std::vector<std::unordered_map<std::string, PatientRoomInfo>> patientroomInfos = problemData.getPreprocessedRooms();

    std::vector<std::unordered_map<std::string, RoomInfo>> roomInfos;
    std::vector<std::unordered_map<std::string, SurgeonOTInfo>> surgeonsOTInfo;
    std::unordered_map<std::string, std::set<std::string>> patientToNurses;
    std::vector<std::unordered_map<std::string, std::set<std::string>>> surgeonToOTPerDay;
    std::unordered_map<std::string, NurseWorkload> nurseIdsToWorloads;

    const auto& days = problemData.getDays();
    const auto& allShiftTypes = problemData.getShiftTypes();
    const auto& operationTheathers = problemData.getOperatingTheaters();
    const auto& problemSurgeons = problemData.getSurgeons();

    roomInfos.reserve(days);
    surgeonsOTInfo.reserve(days);
    patientToNurses.reserve(problemData.getPatients().size());
    surgeonToOTPerDay.reserve(days);
    nurseIdsToWorloads.reserve(problemData.getNurses().size());

    
    std::transform(
        patientroomInfos.begin(), 
        patientroomInfos.end(),
        std::back_inserter(roomInfos),
        [](const std::unordered_map<std::string, PatientRoomInfo>& originalMap)
        {
            std::unordered_map<std::string, RoomInfo> newMap;
            newMap.reserve(originalMap.size());

            for (const auto& pair : originalMap) 
            {
                newMap[pair.first] = RoomInfo(pair.second);
            }

            return newMap;
        }
    );

    for (const auto& nurse : solution.getNurses())
    {
        for (const auto& assignment : nurse.getAssignments())
        {
            for (const auto& room : assignment.getRooms())
            {
                roomInfos[assignment.getDay()][room].nurseIdToShift[nurse.getId()] = assignment.getShift();
                roomInfos[assignment.getDay()][room].shiftToNurseId[assignment.getShift()] = nurse.getId();
            }
        }
    }

    for (const auto& solutionPatients : solution.getPatients())
    {
        const auto& admissionDay = solutionPatients.getAdmissionDay();
        const auto patient = problemData.getPatientMap().at(solutionPatients.getId());

        for (int i = 0; i < patient.getLengthOfStay(); ++i)
        {
            auto& room = roomInfos[i + admissionDay].at(solutionPatients.getRoomId());

            ++room.ageGroups[patient.getAgeGroup()];
            ++room.genders[patient.getGender()];

            --room.currentCapacity;

            for (int j = 0; j < allShiftTypes.size(); ++j)
            {
                const auto& shiftType = allShiftTypes[j];
                const auto& offset = i * allShiftTypes.size() + j;

                room.skillLevelRequired[shiftType] = std::max(room.skillLevelRequired[shiftType], patient.getSkillLevelRequired()[offset]);
                room.shiftNameToProducedWorkload[shiftType] += patient.getSkillLevelRequired()[offset];
            }

            room.patientIds.insert(patient.getId());

            for (const auto& nursePair : room.nurseIdToShift)
            {
                patientToNurses[patient.getId()].insert(nursePair.first);
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
        const auto patient = problemData.getPatientMap().at(solutionPatient.getId());
        const auto& operatingTheater = solutionPatient.getOperationTheater();
        const auto surgeon = problemData.getSurgeonMap()[patient.getSurgeonId()];

        auto& workingTime = surgeonsOTInfo[admissionDay][operatingTheater].surgeonsOperations[surgeon.getId()];

        workingTime.actualWorkingTime += patient.getSurgeryDuration();
        workingTime.maxSurgeonCapacity = surgeon.getMaxSurgeryTime()[admissionDay];
    }

    for (int i = 0; i < days; i++)
    {
        for (const auto& room : roomInfos[i])
        {
            const auto& roomValue = room.second;

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

            if (roomValue.shiftToNurseId.size() < allShiftTypes.size())
            {
                res.countUncoveredRoomHard += allShiftTypes.size() - roomValue.shiftToNurseId.size();
            }

            for (const auto& skillReq : roomValue.skillLevelRequired)
            {
                auto it = roomValue.shiftToNurseId.find(skillReq.first);

                if (it != roomValue.shiftToNurseId.end())
                {
                    const auto nurse = problemData.getNursesMap()[it->second];
                    const auto& nurseSkillLevel = nurse.getSkillLevel();

                    if (skillReq.second > nurseSkillLevel) 
                    {
                        res.countMinimumSkillLevelExceeded += skillReq.second - nurseSkillLevel;
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

                    if (shiftWorkloadPair.second > nurseWorkload)
                    {
                        res.countMaximumWorkloadExcceeded += shiftWorkloadPair.second - nurseWorkload;
                    }
                }
            }

            for (const auto& nurse : problemData.getNurses())
            {
                auto it = roomValue.nurseIdToShift.find(nurse.getId());
                bool isNurseFound  = it != roomValue.nurseIdToShift.end();

                if (isNurseFound && nurse.getWorkloadByDayAndShift(i, it->second) <= 0)
                {
                    ++res.countNursePresentOnWrongDayHard;
                }
            }
        } 
    }

    for (const auto& patient : solution.getPatients())
    {
        const auto patientFromProblem = problemData.getPatientMap().at(patient.getId());

        if (patient.getAdmissionDay() < 0)
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
            ++res.countAdmissionDelay;
        }
    }

    for (int i = 0; i < surgeonsOTInfo.size(); ++i)
    {
        std::unordered_map<std::string, std::set<std::string>> surgeonsToOTs;
        surgeonsToOTs.reserve(problemSurgeons.size());

        for (const auto& pair : surgeonsOTInfo[i])
        {
            const auto& ot = pair.second;

            ++res.countOpenOTs;

            if (ot.isOTOvercrowded())
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

    for (const auto& patientToNurse : patientToNurses)
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

    return res;
}