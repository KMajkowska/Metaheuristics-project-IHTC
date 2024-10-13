#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Assignment
{
public:
	int getDay() const;
	void setDay(int newDay);

	std::string getShift() const;
	void setShift(const std::string& newShift);

	std::string getRoomId() const;
	void setRoomId(const std::string& newRoomId);

private:
	int day;
	std::string shift;
	std::string roomId;
};


void to_json(nlohmann::json& j, const Assignment& data);
void from_json(const nlohmann::json& j, Assignment& data);