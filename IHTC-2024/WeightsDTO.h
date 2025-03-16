#pragma once

#include <nlohmann/json.hpp>

/**
 * @brief Json data provide also weights for all soft restrictions
 * There are no weights for hard restrictions, beacues the cannot be broken in solution.
 * However we need this weights to calculate fitness of solution, so the weight of it is the highest soft restriction multiplied by a choosen number
*/
class WeightsDTO
{
public:
	int getRoomMixedAge() const;
	int getRoomNurseSkill() const;
	int getContinuityOfCare() const;
	int getNurseEccessiveWorkload() const;
	int getOpenOperatingTheater() const;
	int getSurgeonTransfer() const;
	int getPatientDelay() const;
	int getUnscheduledOptional() const;

	void setRoomMixedAge(int newRoomMixedAge);
	void setRoomNurseSkill(int newRoomNurseSkill);
	void setContinuityOfCare(int newContinuityOfCare);
	void setNurseEccessiveWorkload(int newNurseEccessiveWorkload);
	void setOpenOperatingTheater(int newOpenOperatingTheater);
	void setSurgeonTransfer(int newSurgeonTransfer);
	void setPatientDelay(int newPatientDelay);
	void setUnscheduledOptional(int newUnscheduledOptional);

	int getMaxWeight() const;

private:
	int _roomMixedAge { 0 };
	int _roomNurseSkill { 0 };
	int _continuityOfCare { 0 };
	int _nurseEccessiveWorkload { 0 };	// typo in excessive - exists in file
	int _openOperatingTheater { 0 };
	int _surgeonTransfer { 0 };
	int _patientDelay { 0 };
	int _unscheduledOptional { 0 };
};

void to_json(nlohmann::json& j, const WeightsDTO& weights);
void from_json(const nlohmann::json& j, WeightsDTO& weights);