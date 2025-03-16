#include "ProblemData.h"
#include "OperatingTheaterWrapper.h"

int ProblemData::days() const
{
    return _days;
}

int ProblemData::skillLevels() const
{
    return _skill_levels;
}

std::vector<std::string> ProblemData::shiftTypes() const
{
    return _shiftTypes;
}

std::vector<std::string> ProblemData::ageGroups() const
{
    return _ageGroups;
}

WeightsDTO ProblemData::weights() const
{
    return _weights;
}

std::vector<NurseDTO> ProblemData::nurses() const
{
    return _nurses;
}

std::vector<RoomDTO> ProblemData::rooms() const
{
    return _rooms;
}

std::vector<OccupantDTO> ProblemData::occupants() const
{
    return _occupants;
}

std::vector<IncomingPatientDTO> ProblemData::patients() const
{
    return _patients;
}

std::vector<SurgeonDTO> ProblemData::surgeons() const
{
    return _surgeons;
}

std::vector<OperatingTheaterDTO> ProblemData::operatingTheaters() const
{
    return _operatingTheaters;
}

std::vector<std::vector<OperatingTheaterWrapper>> ProblemData::operatingTheatersAvailability() const
{
    return _operatingTheatersAvailability;
}

void ProblemData::setDays(int newDays)
{
    _days = newDays;

    runOperatingTheatersPreprocessing();
    runOperatingTheatersAvailibility();
}

void ProblemData::setSkillLevels(int newSkillLevels)
{
    _skill_levels = newSkillLevels;
}

void ProblemData::setShiftTypes(std::vector<std::string> newShiftTypes)
{
    _shiftTypes = newShiftTypes;

    _shiftTypeToIndexMap.clear();

    _shiftTypeToIndexMap.reserve(_shiftTypes.size());
    for (int i = 0; i < _shiftTypes.size(); ++i)
    {
        _shiftTypeToIndexMap[_shiftTypes[i]] = i;
    }
}

void ProblemData::setAgeGroups(std::vector<std::string> newAgeGroups)
{
    _ageGroups = newAgeGroups;
}

void ProblemData::setWeights(WeightsDTO newWeights)
{
    _weights = newWeights;
}

void ProblemData::setNurses(std::vector<NurseDTO> newNurses)
{
    _nurses = newNurses;

    _nursesMap.clear();

    _nursesMap.reserve(_nurses.size());
    for (const auto& nurse : _nurses)
    {
        _nursesMap[nurse.id()] = nurse;
    }
}

void ProblemData::setRooms(std::vector<RoomDTO> newRooms)
{
    _rooms = newRooms;

    runPreprocessing();
}

void ProblemData::setOccupants(std::vector<OccupantDTO> newOccupants)
{
    _occupants = newOccupants;

    runPreprocessing();
}

void ProblemData::setPatients(std::vector<IncomingPatientDTO> newPatients)
{
    _patients = newPatients;

    _patientMap.clear();

    _patientMap.reserve(_patients.size());
    for (const auto& patient : _patients)
    {
        _patientMap[patient.id()] = patient;
    }

    runPreprocessing();
}

void ProblemData::setSurgeons(std::vector<SurgeonDTO> newSurgeons)
{
    _surgeons = newSurgeons;

    _surgeonMap.clear();

    _surgeonMap.reserve(_surgeons.size());
    for (const auto& surgeon : _surgeons)
    {
        _surgeonMap[surgeon.id()] = surgeon;
    }
}

void ProblemData::setOperatingTheaters(std::vector<OperatingTheaterDTO> newTheaters)
{
    _operatingTheaters = newTheaters;

    runOperatingTheatersPreprocessing();
    runOperatingTheatersAvailibility();
}

RoomWithOccupancyRepresentation ProblemData::getPreprocessedRooms() const
{
    return _roomInfos;
}

std::unordered_map<std::string, SurgeonDTO> ProblemData::getSurgeonMap() const
{
    return _surgeonMap;
}

std::unordered_map<std::string, IncomingPatientDTO> ProblemData::getPatientMap() const
{
    return _patientMap;
}

std::unordered_map<std::string, NurseDTO> ProblemData::getNursesMap() const
{
    return _nursesMap;
}

std::vector<std::unordered_map<std::string, std::vector<std::string>>> ProblemData::getEmptyOperatingTheaters() const
{
    return _emptyOperatingTheaters;
}

int ProblemData::getOffsetOfShiftTypes(std::string shiftType) const
{
    return _shiftTypeToIndexMap.at(shiftType);
}

std::unordered_map<std::string, int> ProblemData::getShiftTypeToIndexMap() const
{
    return _shiftTypeToIndexMap;
}

void ProblemData::runPreprocessing()
{
    _roomInfos = RoomWithOccupancyRepresentation(_rooms, _occupants, _patients, _shiftTypes, _days);
}

void ProblemData::runOperatingTheatersPreprocessing()
{
    _emptyOperatingTheaters.clear();
    _emptyOperatingTheaters.reserve(_days);

    for (int i = 0; i < _days; ++i)
    {
        std::unordered_map<std::string, std::vector<std::string>> newMap;
        newMap.reserve(_operatingTheaters.size());

        _emptyOperatingTheaters.push_back(newMap);

        for (const auto& ot : _operatingTheaters)
        {
            if (ot.getAvailability()[i] > 0)
            {
                std::vector<std::string> patients;
                _emptyOperatingTheaters[i][ot.id()] = patients;
            }
        }
    }
}

void ProblemData::runOperatingTheatersAvailibility()
{
    _operatingTheatersAvailability.clear();
    _operatingTheatersAvailability.reserve(_operatingTheaters.size());

    for (int i = 0; i < _days; ++i)
    {
        std::vector<OperatingTheaterWrapper> ots;

        for (const auto& operatingTheater : _operatingTheaters)
        {
            ots.push_back(
                OperatingTheaterWrapper(
                    OperatingTheaterInfo(operatingTheater.getAvailability().at(i), 0, operatingTheater.id())
                )
            );
        }

        _operatingTheatersAvailability.push_back(ots);
    }
}

void to_json(nlohmann::json& j, const ProblemData& data)
{
    j = nlohmann::json
    {
        {"days", data.days()},
        {"skill_levels", data.skillLevels()},
        {"shift_types", data.shiftTypes()},
        {"age_groups", data.ageGroups()},
        {"weights", data.weights()},
        {"nurses", data.nurses()},
        {"rooms", data.rooms()},
        {"occupants", data.occupants()},
        {"patients", data.patients()},
        {"surgeons", data.surgeons()},
        {"operating_theaters", data.operatingTheaters()}
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

