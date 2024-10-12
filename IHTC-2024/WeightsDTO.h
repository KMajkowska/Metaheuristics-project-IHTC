#pragma once

#include <nlohmann/json.hpp>

class WeightsDTO
{
public:
	int getRoomMixedAge() const;
	int getRoomNurseSkill() const;
	int getContinuityOfCare() const;
	int getNurseEccesiveWorkload() const;
	int getOpenOperatingTheater() const;
	int getSurgeonTransfer() const;
	int getPatientDelay() const;
	int getUnscheduledOptional() const;

	void setRoomMixedAge(int newRoomMixedAge);
	void setRoomNurseSkill(int newRoomNurseSkill);
	void setContinuityOfCare(int newContinuityOfCare);
	void setNurseEccesiveWorkload(int newNurseEccesiveWorkload);
	void setOpenOperatingTheater(int newOpenOperatingTheater);
	void setSurgeonTransfer(int newSurgeonTransfer);
	void setPatientDelay(int newPatientDelay);
	void setUnscheduledOptional(int newUnscheduledOptional);

private:
	int room_mixed_age;
	int room_nurse_skill;
	int continuity_of_care;
	int nurse_eccesive_workload;	// typo in excessive - exists in file
	int open_operating_theater;
	int surgeon_transfer;
	int patient_delay;
	int unscheduled_optional;
};

void to_json(nlohmann::json& j, const WeightsDTO& weights);