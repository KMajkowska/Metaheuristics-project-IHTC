#include "ViolatedRestrictions.h"

std::ostream& operator<<(std::ostream& os, const ViolatedRestrictions& data)
{
	os << std::endl << "{" << std::endl

		// start :: hard restrictions					
		<< "countGenderMixHard: " << data.countGenderMixHard() << std::endl
		<< "countIncompatibleRoomsHard: " << data.countIncompatibleRoomsHard() << std::endl
		<< "countOvercrowdedCapacityHard: " << data.countOvercrowdedCapacityHard() << std::endl
		<< "countUnadmittedMandatoryHard: " << data.countUnadmittedMandatoryHard() << std::endl
		<< "countLateAdmittedMandatoryHard: " << data.countLateAdmittedMandatoryHard() << std::endl
		<< "countSurgeonOvertimeHard: " << data.countSurgeonOvertimeHard() << std::endl
		<< "countOTOvertimeHard: " << data.countOTOvertimeHard() << std::endl
		<< "countUncoveredRoomHard: " << data.countUncoveredRoomHard() << std::endl
		<< "countNursePresentOnWrongDayHard: " << data.countNursePresentOnWrongDayHard() << std::endl
		// end :: hard restrictions					

		// begin :: soft restrictions
		<< "countMixedAgeGroups: " << data.countMixedAgeGroups() << std::endl
		<< "countMinimumSkillLevelExceeded: " << data.countMinimumSkillLevelExceeded() << std::endl
		<< "countUncontinuousCare: " << data.countUncontinuousCare() << std::endl
		<< "countMaximumWorkloadExcceeded: " << data.countMaximumWorkloadExcceeded()<< std::endl
		<< "countOpenOTs: " << data.countOpenOTs() << std::endl
		<< "countSurgeonTransfer: " << data.countSurgeonTransfer() << std::endl
		<< "countAdmissionDelay: " << data.countAdmissionDelay() << std::endl
		<< "countUncheduledOptional: " << data.countUncheduledOptional() << std::endl
		// end :: soft restrictions

		<< "}\tTOTAL HARD: " << data.countTotalHard() << "\tTOTAL SOFT: " << data.countTotalSoft() << std::endl;

	return os;
}

int ViolatedRestrictions::countTotalHard() const
{
	int countTotalHard = 0;

	countTotalHard += countGenderMixHard();
	countTotalHard += countIncompatibleRoomsHard();
	countTotalHard += countOvercrowdedCapacityHard();
	countTotalHard += countUnadmittedMandatoryHard();
	countTotalHard += countLateAdmittedMandatoryHard();
	countTotalHard += countSurgeonOvertimeHard();
	countTotalHard += countOTOvertimeHard();
	countTotalHard += countUncoveredRoomHard();
	countTotalHard += countNursePresentOnWrongDayHard();

	return countTotalHard;

}

int ViolatedRestrictions::countTotalSoft() const
{
	int countTotalSoft = 0;

	countTotalSoft += countMixedAgeGroups();
	countTotalSoft += countMinimumSkillLevelExceeded();
	countTotalSoft += countUncontinuousCare();
	countTotalSoft += countMaximumWorkloadExcceeded();
	countTotalSoft += countOpenOTs();
	countTotalSoft += countSurgeonTransfer();
	countTotalSoft += countAdmissionDelay();
	countTotalSoft += countUncheduledOptional();

	return countTotalSoft;
}

std::string ViolatedRestrictions::getCSVColumns(const std::string& suffix) const
{
	std::stringstream ss;

	ss << "countGenderMixHard" << suffix
		<< ",countIncompatibleRoomsHard" << suffix
		<< ",countOvercrowdedCapacityHard" << suffix
		<< ",countUnadmittedMandatoryHard" << suffix
		<< ",countLateAdmittedMandatoryHard" << suffix
		<< ",countSurgeonOvertimeHard" << suffix
		<< ",countOTOvertimeHard" << suffix
		<< ",countUncoveredRoomHard" << suffix
		<< ",countNursePresentOnWrongDayHard" << suffix

		<< ",countMixedAgeGroups" << suffix
		<< ",countMinimumSkillLevelExceeded" << suffix
		<< ",countUncontinuousCare" << suffix
		<< ",countMaximumWorkloadExcceeded" << suffix
		<< ",countOpenOTs" << suffix
		<< ",countSurgeonTransfer" << suffix
		<< ",countAdmissionDelay" << suffix
		<< ",countUncheduledOptional" << suffix

		<< ",countTotalHard" << suffix
		<< ",countTotalSoft" << suffix;

	return ss.str();
}

std::string ViolatedRestrictions::getCSVData() const
{
	std::stringstream ss;

	ss << countGenderMixHard() << ","
		<< countIncompatibleRoomsHard() << ","
		<< countOvercrowdedCapacityHard() << ","
		<< countUnadmittedMandatoryHard() << ","
		<< countLateAdmittedMandatoryHard() << ","
		<< countSurgeonOvertimeHard() << ","
		<< countOTOvertimeHard() << ","
		<< countUncoveredRoomHard() << ","
		<< countNursePresentOnWrongDayHard() << ","

		<< countMixedAgeGroups() << ","
		<< countMinimumSkillLevelExceeded() << ","
		<< countUncontinuousCare() << ","
		<< countMaximumWorkloadExcceeded() << ","
		<< countOpenOTs() << ","
		<< countSurgeonTransfer() << ","
		<< countAdmissionDelay() << ","
		<< countUncheduledOptional() << ","

		<< countTotalHard() << ","
		<< countTotalSoft();

	return ss.str();
}

bool ViolatedRestrictions::operator==(const ViolatedRestrictions& other) const
{
	return _countGenderMixHard == other._countGenderMixHard
		&& _countIncompatibleRoomsHard == other._countIncompatibleRoomsHard
		&& _countOvercrowdedCapacityHard == other._countOvercrowdedCapacityHard
		&& _countUnadmittedMandatoryHard == other._countUnadmittedMandatoryHard
		&& _countLateAdmittedMandatoryHard == other._countLateAdmittedMandatoryHard
		&& _countSurgeonOvertimeHard == other._countSurgeonOvertimeHard
		&& _countOTOvertimeHard == other._countOTOvertimeHard
		&& _countUncoveredRoomHard == other._countUncoveredRoomHard
		&& _countNursePresentOnWrongDayHard == other._countNursePresentOnWrongDayHard

		&& _countMixedAgeGroups == other._countMixedAgeGroups
		&& _countMinimumSkillLevelExceeded == other._countMinimumSkillLevelExceeded
		&& _countUncontinuousCare == other._countUncontinuousCare
		&& _countMaximumWorkloadExcceeded == other._countMaximumWorkloadExcceeded
		&& _countOpenOTs == other._countOpenOTs
		&& _countSurgeonTransfer == other._countSurgeonTransfer
		&& _countAdmissionDelay == other._countAdmissionDelay
		&& _countUncheduledOptional == other._countUncheduledOptional;
}

void ViolatedRestrictions::setCountGenderMixHard()
{
	++_countGenderMixHard;
}

void ViolatedRestrictions::setCountIncompatibleRoomsHard()
{
	++_countIncompatibleRoomsHard;
}

void ViolatedRestrictions::setCountOvercrowdedCapacityHard()
{
	++_countOvercrowdedCapacityHard;
}

void ViolatedRestrictions::setCountUnadmittedMandatoryHard()
{
	++_countUnadmittedMandatoryHard;
}

void ViolatedRestrictions::setCountLateAdmittedMandatoryHard()
{
	++_countLateAdmittedMandatoryHard;
}

void ViolatedRestrictions::setCountSurgeonOvertimeHard()
{
	++_countSurgeonOvertimeHard;
}

void ViolatedRestrictions::setCountOTOvertimeHard()
{
	++_countOTOvertimeHard;
}

void ViolatedRestrictions::setCountUncoveredRoomHard(int countUncoveredRoomHard)
{
	_countUncoveredRoomHard += countUncoveredRoomHard;
}

void ViolatedRestrictions::setCountNursePresentOnWrongDayHard()
{
	++_countNursePresentOnWrongDayHard;
}

void ViolatedRestrictions::setCountMixedAgeGroups()
{
	++_countMixedAgeGroups;
}

void ViolatedRestrictions::setCountMinimumSkillLevelExceeded(int countMinimumSkillLevelExceeded)
{
	_countMinimumSkillLevelExceeded += countMinimumSkillLevelExceeded;
}

void ViolatedRestrictions::setCountUncontinuousCare(int countUncontinuousCare)
{
	_countUncontinuousCare += countUncontinuousCare;
}

void ViolatedRestrictions::setCountMaximumWorkloadExcceeded(int countMaximumWorkloadExcceeded)
{
	_countMaximumWorkloadExcceeded += countMaximumWorkloadExcceeded;

}

void ViolatedRestrictions::setCountOpenOTs(int countOpenOTs)
{
	_countOpenOTs += countOpenOTs;
}

void ViolatedRestrictions::setCountSurgeonTransfer()
{
	++_countSurgeonTransfer;
}

void ViolatedRestrictions::setCountAdmissionDelay(int countAdmissionDelay)
{
	_countAdmissionDelay += countAdmissionDelay;
}

void ViolatedRestrictions::setCountUncheduledOptional()
{
	++_countUncheduledOptional;
}

int ViolatedRestrictions::countGenderMixHard() const
{
	return _countGenderMixHard;
}

int ViolatedRestrictions::countIncompatibleRoomsHard() const
{
	return _countIncompatibleRoomsHard;
}

int ViolatedRestrictions::countOvercrowdedCapacityHard() const
{
	return _countOvercrowdedCapacityHard;
}

int ViolatedRestrictions::countUnadmittedMandatoryHard() const
{
	return _countUnadmittedMandatoryHard;
}

int ViolatedRestrictions::countLateAdmittedMandatoryHard() const
{
	return _countLateAdmittedMandatoryHard;
}

int ViolatedRestrictions::countSurgeonOvertimeHard() const
{
	return _countSurgeonOvertimeHard;
}

int ViolatedRestrictions::countOTOvertimeHard() const
{
	return _countOTOvertimeHard;
}

int ViolatedRestrictions::countUncoveredRoomHard() const
{
	return _countUncoveredRoomHard;
}

int ViolatedRestrictions::countNursePresentOnWrongDayHard() const
{
	return _countNursePresentOnWrongDayHard;
}

int ViolatedRestrictions::countMixedAgeGroups() const
{
	return _countMixedAgeGroups;
}

int ViolatedRestrictions::countMinimumSkillLevelExceeded() const
{
	return _countMinimumSkillLevelExceeded;
}

int ViolatedRestrictions::countUncontinuousCare() const
{
	return _countUncontinuousCare;
}

int ViolatedRestrictions::countMaximumWorkloadExcceeded() const
{
	return _countMaximumWorkloadExcceeded;
}

int ViolatedRestrictions::countOpenOTs() const
{
	return _countOpenOTs;
}

int ViolatedRestrictions::countSurgeonTransfer() const
{
	return _countSurgeonTransfer;
}

int ViolatedRestrictions::countAdmissionDelay() const
{
	return _countAdmissionDelay;
}

int ViolatedRestrictions::countUncheduledOptional() const
{
	return _countUncheduledOptional;
}
