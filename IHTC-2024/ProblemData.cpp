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

void ProblemData::setDays(int newDays)
{
    days = newDays;
}

void ProblemData::setSkillLevels(int newSkillLevels)
{
    skill_levels = newSkillLevels;
}

void ProblemData::setShiftTypes(std::vector<std::string> newShiftTypes)
{
    shift_types = newShiftTypes;
}

void ProblemData::setAgeGroups(std::vector<std::string> newAgeGroups)
{
    age_groups = newAgeGroups;
}

void ProblemData::setWeights(WeightsDTO& newWeights)
{
    weights = newWeights;
}

void ProblemData::setNurses(std::vector<NurseDTO> newNurses)
{
    nurses = newNurses;
}

void ProblemData::setRooms(std::vector<RoomDTO> newRooms)
{
    rooms = newRooms;
}

void ProblemData::setOccupants(std::vector<OccupantDTO> newOccupants)
{
    occupants = newOccupants;
}

void ProblemData::setPatients(std::vector<IncomingPatientDTO> newPatients)
{
    patients = newPatients;
}
