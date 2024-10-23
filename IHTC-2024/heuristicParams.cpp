#include "heuristicParams.h"

double calculateWeights(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions)
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

double calculateNewTemp(double currTemp, int iteration)
{
    return 0.99 * currTemp;
}
