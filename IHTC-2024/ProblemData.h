#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "WeightsDTO.h"
#include "NurseDTO.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "IncomingPatientDTO.h"

class ProblemData
{
public:
	int getDays() const;
	int getSkillLevels() const;
	std::vector<std::string> getShiftTypes() const;
	std::vector<std::string> getAgeGroups() const;
	WeightsDTO getWeights() const;
	std::vector<NurseDTO> getNurses() const;
	std::vector<RoomDTO> getRooms() const;
	std::vector<OccupantDTO> getOccupants() const;
	std::vector<IncomingPatientDTO> getPatients() const;

	void setDays(int newDays);
	void setSkillLevels(int newSkillLevels);
	void setShiftTypes(std::vector<std::string> newShiftTypes);
	void setAgeGroups(std::vector<std::string> newAgeGroups);
	void setWeights(WeightsDTO newWeights);
	void setNurses(std::vector<NurseDTO> newNurses);
	void setRooms(std::vector<RoomDTO> newRooms);
	void setOccupants(std::vector<OccupantDTO> newOccupants);
	void setPatients(std::vector<IncomingPatientDTO> newIncomingPatients);

private:
	int days;
	int skill_levels;
	std::vector<std::string> shift_types;
	std::vector<std::string> age_groups;
	WeightsDTO weights;
	std::vector<NurseDTO> nurses;
	std::vector<RoomDTO> rooms;
	std::vector<OccupantDTO> occupants;
	std::vector<IncomingPatientDTO> patients;
};

void to_json(nlohmann::json& j, const ProblemData& data);
void from_json(const nlohmann::json& j, ProblemData& data);