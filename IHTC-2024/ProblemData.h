#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "WeightsDTO.h"
#include "NurseDTO.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "IncomingPatientDTO.h"
#include "SurgeonDTO.h"
#include "OperatingTheaterDTO.h"
#include "RoomInfo.h"
#include "RoomWithOccupancyRepresentation.h"
#include "OperatingTheaterWrapper.h"

class ProblemData
{
public:
	ProblemData() = default;
	ProblemData(const ProblemData& other) = default;

	int getDays() const;
	int getSkillLevels() const;
	std::vector<std::string> getShiftTypes() const;
	std::vector<std::string> getAgeGroups() const;
	WeightsDTO getWeights() const;
	std::vector<NurseDTO> getNurses() const;
	std::vector<RoomDTO> getRooms() const;
	std::vector<OccupantDTO> getOccupants() const;
	std::vector<IncomingPatientDTO> getPatients() const;
	std::vector<SurgeonDTO> getSurgeons() const;
	std::vector<OperatingTheaterDTO> getOperatingTheaters() const;
	std::vector<std::vector<OperatingTheaterWrapper>> getOperatingTheatersAvailability() const;

	void setDays(int newDays);
	void setSkillLevels(int newSkillLevels);
	void setShiftTypes(std::vector<std::string> newShiftTypes);
	void setAgeGroups(std::vector<std::string> newAgeGroups);
	void setWeights(WeightsDTO newWeights);
	void setNurses(std::vector<NurseDTO> newNurses);
	void setRooms(std::vector<RoomDTO> newRooms);
	void setOccupants(std::vector<OccupantDTO> newOccupants);
	void setPatients(std::vector<IncomingPatientDTO> newIncomingPatients);
	void setSurgeons(std::vector<SurgeonDTO> newSurgeons);
	void setOperatingTheaters(std::vector<OperatingTheaterDTO> newTheaters);

	RoomWithOccupancyRepresentation getPreprocessedRooms() const;
	std::unordered_map<std::string, SurgeonDTO> getSurgeonMap() const;
	std::unordered_map<std::string, IncomingPatientDTO> getPatientMap() const;
	std::unordered_map<std::string, NurseDTO> getNursesMap() const;
	std::vector<std::unordered_map<std::string, std::vector<std::string>>> getEmptyOperatingTheaters() const;
	std::unordered_map<std::string, int> getShiftTypeToIndexMap() const;
	int getOffsetOfShiftTypes(std::string shiftType) const;

private:
	int days = 0;
	int skill_levels = 0;
	std::vector<std::string> shift_types;
	std::vector<std::string> age_groups;
	WeightsDTO weights;
	std::vector<NurseDTO> nurses;
	std::vector<RoomDTO> rooms;
	std::vector<OccupantDTO> occupants;
	std::vector<IncomingPatientDTO> patients;
	std::vector<SurgeonDTO> surgeons;
	std::vector<OperatingTheaterDTO> operating_theaters;

	RoomWithOccupancyRepresentation roomInfos;
	std::unordered_map<std::string, SurgeonDTO> surgeonMap;
	std::unordered_map<std::string, IncomingPatientDTO> patientMap;
	std::unordered_map<std::string, NurseDTO> nursesMap;
	std::vector<std::unordered_map<std::string, std::vector<std::string>>> empty_operating_theaters;
	std::vector<std::vector<OperatingTheaterWrapper>> operating_theaters_availability;
	std::unordered_map<std::string, int> shiftTypeToIndexMap;

	void runPreprocessing();
	void runOperatingTheatersPreprocessing();
	void runOperatingTheatersAvailibility();
};

void to_json(nlohmann::json& j, const ProblemData& data);
void from_json(const nlohmann::json& j, ProblemData& data);