#include "ProblemData.h"

int ProblemData::getDays() const
{
    return days;
}

int ProblemData::getSkillLevels() const
{
    return skill_levels;
}

std::vector<std::string> ProblemData::getShiftTypes()
{
    return shift_types;
}

std::vector<std::string> ProblemData::getAgeGroups()
{
    return age_groups;
}

WeightsDTO ProblemData::getWeights()
{
    return weights;
}

std::vector<NurseDTO> ProblemData::getNurses()
{
    return nurses;
}

std::vector<RoomDTO> ProblemData::getRooms()
{
    return rooms;
}

std::vector<OccupantDTO> ProblemData::getOccupants()
{
    return occupants;
}

std::vector<IncomingPatientDTO> ProblemData::getPatients()
{
    return patients;
}
