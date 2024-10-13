#include "Patient.h"

Patient::Patient(int admissionDay, const std::string& roomId, const std::string& operationTheater) :
    admissionDay(admissionDay),
    roomId(roomId),
    operationTheater(operationTheater)
{}

int Patient::getAdmissionDay() const
{
	return admissionDay;
}

void Patient::setAdmissionDay(int newAdmissionDay)
{
	admissionDay = newAdmissionDay;
}

std::string Patient::getRoomId() const
{
	return roomId;
}

void Patient::setRoomId(const std::string& newRoomId)
{
	roomId = newRoomId;
}

std::string Patient::getOperationTheater() const
{
	return operationTheater;
}

void Patient::setOperationTheater(const std::string& newOperationTheater)
{
	operationTheater = newOperationTheater;
}

void to_json(nlohmann::json& j, const Patient& data)
{
    j = nlohmann::json
    {
        {"admission_day", data.getAdmissionDay()},
        {"room_id", data.getRoomId()},
        {"operation_theater", data.getOperationTheater()},
    };
}

void from_json(const nlohmann::json& j, Patient& data)
{
    data.setAdmissionDay(j.at("admission_day").get<int>());
    data.setRoomId(j.at("room_id").get<std::string>());
    data.setOperationTheater(j.at("operation_theater").get<std::string>());
}