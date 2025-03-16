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

	int days() const;
	int skillLevels() const;
	std::vector<std::string> shiftTypes() const;
	std::vector<std::string> ageGroups() const;
	WeightsDTO weights() const;
	std::vector<NurseDTO> nurses() const;
	std::vector<RoomDTO> rooms() const;
	std::vector<OccupantDTO> occupants() const;
	std::vector<IncomingPatientDTO> patients() const;
	std::vector<SurgeonDTO> surgeons() const;
	std::vector<OperatingTheaterDTO> operatingTheaters() const;
	std::vector<std::vector<OperatingTheaterWrapper>> operatingTheatersAvailability() const;

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
	int _days { 0 };
	int _skill_levels { 0 };
	std::vector<std::string> _shiftTypes;
	std::vector<std::string> _ageGroups;
	WeightsDTO _weights;
	std::vector<NurseDTO> _nurses;
	std::vector<RoomDTO> _rooms;
	std::vector<OccupantDTO> _occupants;
	std::vector<IncomingPatientDTO> _patients;
	std::vector<SurgeonDTO> _surgeons;
	std::vector<OperatingTheaterDTO> _operatingTheaters;

	RoomWithOccupancyRepresentation _roomInfos;
	std::unordered_map<std::string, SurgeonDTO> _surgeonMap;
	std::unordered_map<std::string, IncomingPatientDTO> _patientMap;
	std::unordered_map<std::string, NurseDTO> _nursesMap;
	std::vector<std::unordered_map<std::string, std::vector<std::string>>> _emptyOperatingTheaters;
	std::vector<std::vector<OperatingTheaterWrapper>> _operatingTheatersAvailability;
	std::unordered_map<std::string, int> _shiftTypeToIndexMap;

	void runPreprocessing();
	void runOperatingTheatersPreprocessing();
	void runOperatingTheatersAvailibility();
};

void to_json(nlohmann::json& j, const ProblemData& data);
void from_json(const nlohmann::json& j, ProblemData& data);