#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Assignment
{
public:
	Assignment();
	Assignment(int day, std::string shift, std::vector<std::string> rooms);

	int getDay() const;
	void setDay(int newDay);

	std::string getShift() const;
	void setShift(const std::string& newShift);

	std::vector<std::string> getRooms() const;
	void setRooms(std::vector<std::string> newRooms);

private:
	int day;
	std::string shift;
	std::vector<std::string> rooms;
};


void to_json(nlohmann::json& j, const Assignment& data);
void from_json(const nlohmann::json& j, Assignment& data);