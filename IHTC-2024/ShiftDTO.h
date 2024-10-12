#pragma once

#include <string>

class ShiftDTO
{
public:
	int getDay() const;
	std::string getShift() const;
	int getMaxLoad() const;

private:
	int day;
	std::string shift;
	int max_load;
};