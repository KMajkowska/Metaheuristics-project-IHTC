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

std::vector<SurgeonDTO> ProblemData::getSurgeons() const
{
    return surgeons;
}

std::vector<OperatingTheaterDTO> ProblemData::getOperatingTheaters() const
{
    return operating_theaters;
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

void ProblemData::setWeights(WeightsDTO newWeights)
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

void ProblemData::setSurgeons(std::vector<SurgeonDTO> newSurgeons)
{
    surgeons = newSurgeons;
}

void ProblemData::setOperatingTheaters(std::vector<OperatingTheaterDTO> newTheaters)
{
    operating_theaters = newTheaters;
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
        {"patients", data.getPatients()},
        {"surgeons", data.getSurgeons()},
        {"operating_theaters", data.getOperatingTheaters()}
    };
}

void from_json(const nlohmann::json& j, ProblemData& data)
{
    data.setDays(j.at("days").get<int>());
    data.setSkillLevels(j.at("skill_levels").get<int>());
    data.setShiftTypes(j.at("shift_types").get<std::vector<std::string>>());
    data.setAgeGroups(j.at("age_groups").get<std::vector<std::string>>());
    data.setWeights(j.at("weights").get<WeightsDTO>());
    data.setNurses(j.at("nurses").get<std::vector<NurseDTO>>());
    data.setRooms(j.at("rooms").get<std::vector<RoomDTO>>());
    data.setOccupants(j.at("occupants").get<std::vector<OccupantDTO>>());
    data.setPatients(j.at("patients").get<std::vector<IncomingPatientDTO>>());
    data.setSurgeons(j.at("surgeons").get<std::vector<SurgeonDTO>>());
    data.setOperatingTheaters(j.at("operating_theaters").get<std::vector<OperatingTheaterDTO>>());
}

