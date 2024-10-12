#include "ProblemData.h"

int ProblemData::getDays() const
{
    return days;
}

int ProblemData::getSkillLevels() const
{
    return skill_levels;
}

std::vector<std::string> ProblemData::getShiftTypes() const
{
    return shift_types;
}

std::vector<std::string> ProblemData::getAgeGroups() const
{
    return age_groups;
}

WeightsDTO ProblemData::getWeights() const
{
    return weights;
}

std::vector<NurseDTO> ProblemData::getNurses() const
{
    return nurses;
}

std::vector<RoomDTO> ProblemData::getRooms() const
{
    return rooms;
}

std::vector<OccupantDTO> ProblemData::getOccupants() const
{
    return occupants;
}

std::vector<IncomingPatientDTO> ProblemData::getPatients() const
{
    return patients;
}

void to_json(nlohmann::json& j, const ProblemData& data)
{
	j = nlohmann::json
	{
		{"days", data.getDays()},
		{"skill_levels", data.getSkillLevels()},
		{"shift_types", data.getShiftTypes()},
		{"age_groups", data.getAgeGroups()},
		{"weights", data.getWeights()},
		{"nurses", data.getNurses()},
		{"rooms", data.getRooms()},
		{"occupants", data.getOccupants()},
		{"patients", data.getPatients()}
	};
}
