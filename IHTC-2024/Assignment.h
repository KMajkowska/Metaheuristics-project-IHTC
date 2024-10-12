#pragma once
#include<string>

class Assignment
{
public:
	int getDay() const;
	void setDay(int newDay);

	std::string getShift() const;
	void setShift(const std::string& newShift);

	std::string getRoom() const;
	void setRoomId(const std::string& newRoomId);

private:
	int day;
	std::string shift;
	std::string roomId;
};