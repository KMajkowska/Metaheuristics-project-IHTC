#include "ProblemData.h"
#include "OperatingTheaterWrapper.h"

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

std::vector<std::vector<OperatingTheaterWrapper>> ProblemData::getOperatingTheatersAvailability() const
{
    return operating_theaters_availability;
}

void ProblemData::setDays(int newDays)
{
    days = newDays;

    runOperatingTheatersPreprocessing();
    runOperatingTheatersAvailibility();
}

void ProblemData::setSkillLevels(int newSkillLevels)
{
    skill_levels = newSkillLevels;
}

void ProblemData::setShiftTypes(std::vector<std::string> newShiftTypes)
{
    shift_types = newShiftTypes;

    shiftTypeToIndexMap.clear();

    shiftTypeToIndexMap.reserve(shift_types.size());
    for (int i = 0; i < shift_types.size(); ++i)
    {
        shiftTypeToIndexMap[shift_types[i]] = i;
    }
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

    nursesMap.clear();

    nursesMap.reserve(nurses.size());
    for (const auto& nurse : nurses)
    {
        nursesMap[nurse.getId()] = nurse;
    }
}

void ProblemData::setRooms(std::vector<RoomDTO> newRooms)
{
    rooms = newRooms;

    runPreprocessing();
}

void ProblemData::setOccupants(std::vector<OccupantDTO> newOccupants)
{
    occupants = newOccupants;

    runPreprocessing();
}

void ProblemData::setPatients(std::vector<IncomingPatientDTO> newPatients)
{
    patients = newPatients;

    patientMap.clear();

    patientMap.reserve(patients.size());
    for (const auto& patient : patients)
    {
        patientMap[patient.getId()] = patient;
    }

    runPreprocessing();
}

void ProblemData::setSurgeons(std::vector<SurgeonDTO> newSurgeons)
{
    surgeons = newSurgeons;

    surgeonMap.clear();

    surgeonMap.reserve(surgeons.size());
    for (const auto& surgeon : surgeons)
    {
        surgeonMap[surgeon.getId()] = surgeon;
    }
}

void ProblemData::setOperatingTheaters(std::vector<OperatingTheaterDTO> newTheaters)
{
    operating_theaters = newTheaters;

    runOperatingTheatersPreprocessing();
    runOperatingTheatersAvailibility();
}

RoomWithOccupancyRepresentation ProblemData::getPreprocessedRooms() const
{
    return roomInfos;
}

std::unordered_map<std::string, SurgeonDTO> ProblemData::getSurgeonMap() const
{
    return surgeonMap;
}

std::unordered_map<std::string, IncomingPatientDTO> ProblemData::getPatientMap() const
{
    return patientMap;
}

std::unordered_map<std::string, NurseDTO> ProblemData::getNursesMap() const
{
    return nursesMap;
}

std::vector<std::unordered_map<std::string, std::vector<std::string>>> ProblemData::getEmptyOperatingTheaters() const
{
    return empty_operating_theaters;
}

int ProblemData::getOffsetOfShiftTypes(std::string shiftType) const
{
    return shiftTypeToIndexMap.at(shiftType);
}

std::unordered_map<std::string, int> ProblemData::getShiftTypeToIndexMap() const
{
    return shiftTypeToIndexMap;
}

void ProblemData::runPreprocessing()
{
    roomInfos = RoomWithOccupancyRepresentation(rooms, occupants, patients, shift_types, days);
}

void ProblemData::runOperatingTheatersPreprocessing()
{
    empty_operating_theaters.clear();
    empty_operating_theaters.reserve(days);

    for (int i = 0; i < days; ++i)
    {
        std::unordered_map<std::string, std::vector<std::string>> newMap;
        newMap.reserve(operating_theaters.size());

        empty_operating_theaters.push_back(newMap);

        for (const auto& ot : operating_theaters)
        {
            if (ot.getAvailability()[i] > 0)
            {
                std::vector<std::string> patients;
                empty_operating_theaters[i][ot.getId()] = patients;
            }
        }
    }
}

void ProblemData::runOperatingTheatersAvailibility()
{
    operating_theaters_availability.clear();
    operating_theaters_availability.reserve(operating_theaters.size());

    for (int i = 0; i < days; ++i)
    {
        std::vector<OperatingTheaterWrapper> ots;

        for (const auto& operatingTheater : operating_theaters)
        {
            ots.push_back(
                OperatingTheaterWrapper(
                    OperatingTheaterInfo(operatingTheater.getAvailability().at(i), 0, operatingTheater.getId())
                )
            );
        }

        operating_theaters_availability.push_back(ots);
    }
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

