#include "Patient.h"

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