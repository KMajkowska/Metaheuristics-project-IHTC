#include "Patient.h"

Patient::Patient() : Patient("", 1, "", "")
{
}

Patient::Patient(const std::string& id, int admissionDay, const std::string& roomId, const std::string& operationTheater) :
    _id(id),
    _admissionDay(admissionDay),
    _roomId(roomId),
    _operationTheater(operationTheater)
{}

std::string Patient::id() const
{
    return _id;
}

void Patient::setId(const std::string& newId)
{
    _id = newId;
}

int Patient::admissionDay() const
{
	return _admissionDay;
}

void Patient::setAdmissionDay(int newAdmissionDay)
{
	_admissionDay = newAdmissionDay;
}

std::string Patient::roomId() const
{
	return _roomId;
}

void Patient::setRoomId(const std::string& newRoomId)
{
	_roomId = newRoomId;
}

std::string Patient::operationTheater() const
{
	return _operationTheater;
}

void Patient::setOperationTheater(const std::string& newOperationTheater)
{
	_operationTheater = newOperationTheater;
}

void to_json(nlohmann::json& j, const Patient& data)
{
    j = nlohmann::json
    {
        {"id", data.id()},
        {"admission_day", data.admissionDay()},
        {"room", data.roomId()},
        {"operating_theater", data.operationTheater()},
    };
}

void from_json(const nlohmann::json& j, Patient& data)
{
    data.setId(j.at("id").get<std::string>());
    data.setAdmissionDay(j.at("admission_day").get<int>());
    data.setRoomId(j.at("room").get<std::string>());
    data.setOperationTheater(j.at("operating_theater").get<std::string>());
}
