#pragma once

#include <nlohmann/json.hpp>

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
	int room_mixed_age = 0;
	int room_nurse_skill = 0;
	int continuity_of_care = 0;
	int nurse_eccessive_workload = 0;	// typo in excessive - exists in file
	int open_operating_theater = 0;
	int surgeon_transfer = 0;
	int patient_delay = 0;
	int unscheduled_optional = 0;
};

void to_json(nlohmann::json& j, const WeightsDTO& weights);
void from_json(const nlohmann::json& j, WeightsDTO& weights);