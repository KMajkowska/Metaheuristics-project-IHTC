#pragma once

#include <ostream>
#include <sstream>


/**
* The purpose of this class is to contain all the restrictions. Based on this restrictions we calculate the fitness of the solution. 
* 
* Hard restrictions are the ones, we cannot break. If we break them, the solution is unacceptable (we count it as solution but punish it really strongly).
* Soft restrictions are the ones, we can break, but we want to minimaze broken soft restrictions. Every restrictions has it own weight, provided by the json data.
*/
class ViolatedRestrictions
{
public:
	// begin :: setters
	// begin ::  hard restrictions
	void setCountGenderMixHard();
	void setCountIncompatibleRoomsHard();
	void setCountOvercrowdedCapacityHard();
	void setCountUnadmittedMandatoryHard();
	void setCountLateAdmittedMandatoryHard();

	void setCountSurgeonOvertimeHard();
	void setCountOTOvertimeHard();

	void setCountUncoveredRoomHard(int countUncoveredRoomHard);
	void setCountNursePresentOnWrongDayHard();
	// end ::  hard restrictions

	// begin ::soft restrictions
	void setCountMixedAgeGroups();
	void setCountMinimumSkillLevelExceeded(int countMinimumSkillLevelExceeded);
	void setCountUncontinuousCare(int countUncontinuousCare);
	void setCountMaximumWorkloadExcceeded(int countMaximumWorkloadExcceeded);
	void setCountOpenOTs(int countOpenOTs);
	void setCountSurgeonTransfer();
	void setCountAdmissionDelay(int countAdmissionDelay);
	void setCountUncheduledOptional();
	// end :: soft restrictions
	// end :: setters
	// 
	// begin :: getters
	// begin ::  hard restrictions
	int countGenderMixHard() const;
	int countIncompatibleRoomsHard() const;
	int countOvercrowdedCapacityHard() const;
	int countUnadmittedMandatoryHard() const;
	int countLateAdmittedMandatoryHard() const;

	int countSurgeonOvertimeHard() const;
	int countOTOvertimeHard() const;
	
	int countUncoveredRoomHard() const;
	int countNursePresentOnWrongDayHard() const;
	// end ::  hard restrictions

	// begin ::soft restrictions
	int countMixedAgeGroups() const;
	int countMinimumSkillLevelExceeded() const;
	int countUncontinuousCare() const;
	int countMaximumWorkloadExcceeded() const;
	int countOpenOTs() const;
	int countSurgeonTransfer() const;
	int countAdmissionDelay() const;
	int countUncheduledOptional() const;
	// end :: soft restrictions
	// end :: getters

	int countTotalHard() const;
	int countTotalSoft() const;

	std::string getCSVColumns(const std::string& suffix) const;
	std::string getCSVData() const;

	bool operator==(const ViolatedRestrictions& other) const;
private:
	// begin :: hard restrictions
	int _countGenderMixHard{ 0 };
	int _countIncompatibleRoomsHard { 0 };
	int _countOvercrowdedCapacityHard { 0 };
	int _countUnadmittedMandatoryHard { 0 };
	int _countLateAdmittedMandatoryHard { 0 };

	int _countSurgeonOvertimeHard { 0 };
	int _countOTOvertimeHard { 0 };

	int _countUncoveredRoomHard { 0 };
	int _countNursePresentOnWrongDayHard { 0 };
	// end :: hard restrictions

	// begin :: soft restrictions
	int _countMixedAgeGroups { 0 };
	int _countMinimumSkillLevelExceeded { 0 };
	int _countUncontinuousCare { 0 };
	int _countMaximumWorkloadExcceeded { 0 };
	int _countOpenOTs { 0 };
	int _countSurgeonTransfer { 0 };
	int _countAdmissionDelay { 0 };
	int _countUncheduledOptional { 0 };
	// end :: soft restrictions
};

std::ostream& operator<<(std::ostream& os, const ViolatedRestrictions& data);