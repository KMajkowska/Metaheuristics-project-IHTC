#pragma once

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Part of individual to analyze rooms assignemnts
 * Every assignemnt is recognized as its day, shift and rooms which need to be covered on this shift. 
 * Individual contains vector of this assignemnt in the map nurseId to vector as assignments.
*/
class Assignment
{
public:
	Assignment();
	Assignment(int day, std::string shift);
	Assignment(int day, std::string shift, std::vector<std::string> rooms);
	Assignment(const Assignment& other) = default;

	int getDay() const;
	void setDay(int newDay);

	std::string getShift() const;
	void setShift(const std::string& newShift);

	std::vector<std::string> getRooms() const;
	void setRooms(std::vector<std::string> newRooms);

	void appendRoom(const std::string& roomId);

private:
	int day;
	std::string shift;
	std::vector<std::string> rooms;
};


void to_json(nlohmann::json& j, const Assignment& data);
void from_json(const nlohmann::json& j, Assignment& data);