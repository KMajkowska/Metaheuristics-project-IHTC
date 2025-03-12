#pragma once

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Represents our patient, whose we need to assign to room, day an OT during solving our problem. Every patient has its own ID, which is given bvy problemData.
*/
class Patient
{
public:
	Patient();
	Patient(const std::string& id, int admissionDay, const std::string& roomId, const std::string& operationTheater);
	Patient(const Patient& patient) = default;

	std::string getId() const;
	void setId(const std::string& newId);

	int getAdmissionDay() const;
	void setAdmissionDay(int newAdmissionDay);

	std::string getRoomId() const;
	void setRoomId(const std::string& newRoomId);

	std::string getOperationTheater() const;
	void setOperationTheater(const std::string& newOperatingTheater);

protected:
	std::string id;
	int admissionDay;
	std::string roomId;
	std::string operationTheater;
};

void to_json(nlohmann::json& j, const Patient& data);
void from_json(const nlohmann::json& j, Patient& data);