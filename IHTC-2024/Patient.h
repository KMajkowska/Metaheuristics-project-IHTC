#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Patient
{
public:
	Patient();
	Patient(const std::string& id, int admissionDay, const std::string& roomId, const std::string& operationTheater);
	Patient(const Patient& patient) = default;

	void setId(const std::string& newId);
	void setRoomId(const std::string& newRoomId);
	void setOperationTheater(const std::string& newOperatingTheater);
	void setAdmissionDay(int newAdmissionDay);

	std::string id() const;
	std::string roomId() const;
	std::string operationTheater() const;
	int admissionDay() const;

protected:
	std::string _id;
	std::string _roomId;
	std::string _operationTheater;
	int _admissionDay;
};

void to_json(nlohmann::json& j, const Patient& data);
void from_json(const nlohmann::json& j, Patient& data);