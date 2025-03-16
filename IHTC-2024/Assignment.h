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

	void setDay(int newDay);
	void setShift(const std::string& newShift);
	void setRooms(std::vector<std::string> newRooms);

	std::string shift() const;
	std::vector<std::string> rooms() const;
	int day() const;

	void appendRoom(const std::string& roomId);

private:
	int _day;
	std::string _shift;
	std::vector<std::string> _rooms;
};


void to_json(nlohmann::json& j, const Assignment& data);
void from_json(const nlohmann::json& j, Assignment& data);