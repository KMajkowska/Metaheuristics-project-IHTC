#pragma once

/**
 * @brief Class to store info about surgeon max working time and actual working time on given day
*/
class SurgeonsTime
{
public:
	SurgeonsTime() = default;
	SurgeonsTime(int maxSurgeonCapacity, int actualWorkingTime);

	void setMaxSurgeonCapacity(int maxSurgeonCapacity);
	void setActualWorkingTime(int actualWorkingTime);

	int maxSurgeonCapacity() const;
	int actualWorkingTime() const;

private:
	int _maxSurgeonCapacity = 0;
	int _actualWorkingTime = 0;
};