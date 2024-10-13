#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Patient
{
public:
	Patient() = default;
	Patient(int admissionDay, const std::string& roomId, const std::string& operationTheater);

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

void to_json(nlohmann::json& j, const Patient& data);
void from_json(const nlohmann::json& j, Patient& data);