#pragma once

#include <string>
#include <vector>

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
	std::vector<std::string> getShiftTypes();
	std::vector<std::string> getAgeGroups();
	WeightsDTO getWeights();
	std::vector<NurseDTO> getNurses();
	std::vector<RoomDTO> getRooms();
	std::vector<OccupantDTO> getOccupants();
	std::vector<IncomingPatientDTO> getPatients();
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