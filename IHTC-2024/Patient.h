#pragma once
#include<string>

class Patient
{
public:
	int getAdmissionDay() const;
	void setAdmissionDay(int newAdmissionDay);

	std::string getRoomId() const;
	void setRoomId(const std::string& newRoomId);

	std::string getOperationTheater() const;
	void setOperationTheater(const std::string& newOperatingTheater);

protected:
	int admissionDay;
	std::string roomId;
	std::string operationTheater;
};