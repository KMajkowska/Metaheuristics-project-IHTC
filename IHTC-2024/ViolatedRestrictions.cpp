#include "ViolatedRestrictions.h"

std::ostream& operator<<(std::ostream& os, const ViolatedRestrictions& data)
{
	os << std::endl << "{" << std::endl

		// start :: hard restrictions					
		<< "countGenderMixHard: " << data.countGenderMixHard << std::endl
		<< "countIncompatibleRoomsHard: " << data.countIncompatibleRoomsHard << std::endl
		<< "countOvercrowdedCapacityHard: " << data.countOvercrowdedCapacityHard << std::endl
		<< "countUnadmittedMandatoryHard: " << data.countUnadmittedMandatoryHard << std::endl
		<< "countLateAdmittedMandatoryHard: " << data.countLateAdmittedMandatoryHard << std::endl
		<< "countSurgeonOvertimeHard: " << data.countSurgeonOvertimeHard << std::endl
		<< "countOTOvertimeHard: " << data.countOTOvertimeHard << std::endl
		<< "countUncoveredRoomHard: " << data.countUncoveredRoomHard << std::endl
		<< "countNursePresentOnWrongDayHard: " << data.countNursePresentOnWrongDayHard << std::endl
		// end :: hard restrictions					

		// begin :: soft restrictions
		<< "countMixedAgeGroups: " << data.countMixedAgeGroups << std::endl
		<< "countMinimumSkillLevelExceeded: " << data.countMinimumSkillLevelExceeded << std::endl
		<< "countUncontinuousCare: " << data.countUncontinuousCare << std::endl
		<< "countMaximumWorkloadExcceeded: " << data.countMaximumWorkloadExcceeded << std::endl
		<< "countOpenOTs: " << data.countOpenOTs << std::endl
		<< "countSurgeonTransfer: " << data.countSurgeonTransfer << std::endl
		<< "countAdmissionDelay: " << data.countAdmissionDelay << std::endl
		<< "countUncheduledOptional: " << data.countUncheduledOptional << std::endl
		// end :: soft restrictions

		<< "}\tTOTAL HARD: " << data.countTotalHard() << "\tTOTAL SOFT: " << data.countTotalSoft() << std::endl;

	return os;
}

int ViolatedRestrictions::countTotalHard() const
{
	int countTotalHard = 0;

	countTotalHard += countGenderMixHard;
	countTotalHard += countIncompatibleRoomsHard;
	countTotalHard += countOvercrowdedCapacityHard;
	countTotalHard += countUnadmittedMandatoryHard;
	countTotalHard += countLateAdmittedMandatoryHard;
	countTotalHard += countSurgeonOvertimeHard;
	countTotalHard += countOTOvertimeHard;
	countTotalHard += countUncoveredRoomHard;
	countTotalHard += countNursePresentOnWrongDayHard;

	return countTotalHard;

}

int ViolatedRestrictions::countTotalSoft() const
{
	int countTotalSoft = 0;

	countTotalSoft += countMixedAgeGroups;
	countTotalSoft += countMinimumSkillLevelExceeded;
	countTotalSoft += countUncontinuousCare;
	countTotalSoft += countMaximumWorkloadExcceeded;
	countTotalSoft += countOpenOTs;
	countTotalSoft += countSurgeonTransfer;
	countTotalSoft += countAdmissionDelay;
	countTotalSoft += countUncheduledOptional;

	return countTotalSoft;
}

std::string ViolatedRestrictions::getCSVColumns() const
{
	std::stringstream ss;

	ss << "countGenderMixHard,"
		<< "countIncompatibleRoomsHard,"
		<< "countOvercrowdedCapacityHard,"
		<< "countUnadmittedMandatoryHard,"
		<< "countLateAdmittedMandatoryHard,"
		<< "countSurgeonOvertimeHard,"
		<< "countOTOvertimeHard,"
		<< "countUncoveredRoomHard,"
		<< "countNursePresentOnWrongDayHard,"

		<< "countMixedAgeGroups,"
		<< "countMinimumSkillLevelExceeded,"
		<< "countUncontinuousCare,"
		<< "countMaximumWorkloadExcceeded,"
		<< "countOpenOTs,"
		<< "countSurgeonTransfer,"
		<< "countAdmissionDelay,"
		<< "countUncheduledOptional,"

		<< "countTotalHard,"
		<< "countTotalSoft";

	return ss.str();
}

std::string ViolatedRestrictions::getCSVData() const
{
	std::stringstream ss;

	ss << countGenderMixHard << ","
		<< countIncompatibleRoomsHard << ","
		<< countOvercrowdedCapacityHard << ","
		<< countUnadmittedMandatoryHard << ","
		<< countLateAdmittedMandatoryHard << ","
		<< countSurgeonOvertimeHard << ","
		<< countOTOvertimeHard << ","
		<< countUncoveredRoomHard << ","
		<< countNursePresentOnWrongDayHard << ","

		<< countMixedAgeGroups << ","
		<< countMinimumSkillLevelExceeded << ","
		<< countUncontinuousCare << ","
		<< countMaximumWorkloadExcceeded << ","
		<< countOpenOTs << ","
		<< countSurgeonTransfer << ","
		<< countAdmissionDelay << ","
		<< countUncheduledOptional << ","

		<< countTotalHard() << ","
		<< countTotalSoft();

	return ss.str();
}