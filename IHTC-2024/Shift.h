#pragma once

class Shift
{
public:
	int getDay() const;
	std::string getShift() const;
	int getMaxLoad() const;

	void setDay(int newDay);
	void setShift(std::string newShift);
	void setMaxLoad(int newMaxLoad);

private:
	int day;
	std::string shift;
	int max_load;
};
