#pragma once

#include <ostream>
#include <sstream>

struct ViolatedRestrictions
{
	// begin :: hard restrictions
	int countGenderMixHard = 0;
	int countIncompatibleRoomsHard = 0;
	int countOvercrowdedCapacityHard = 0;
	int countUnadmittedMandatoryHard = 0;
	int countLateAdmittedMandatoryHard = 0;

	int countSurgeonOvertimeHard = 0;
	int countOTOvertimeHard = 0;

	int countUncoveredRoomHard = 0;
	int countNursePresentOnWrongDayHard = 0;
	// end :: hard restrictions

	// begin :: soft restrictions
	int countMixedAgeGroups = 0;
	int countMinimumSkillLevelExceeded = 0;
	int countUncontinuousCare = 0;
	int countMaximumWorkloadExcceeded = 0;
	int countOpenOTs = 0;
	int countSurgeonTransfer = 0;
	int countAdmissionDelay = 0;
	int countUncheduledOptional = 0;
	// end :: soft restrictions

	int countTotalHard() const;
	int countTotalSoft() const;

	std::string getCSVColumns() const;
	std::string getCSVData() const;
};

std::ostream& operator<<(std::ostream& os, const ViolatedRestrictions& data);