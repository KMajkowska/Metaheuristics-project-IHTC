#include "SurgeonsTime.h"

SurgeonsTime::SurgeonsTime(int maxSurgeonCapacity, int actualWorkingTime) : 
	_maxSurgeonCapacity(maxSurgeonCapacity),
	_actualWorkingTime(actualWorkingTime)
{}

void SurgeonsTime::setMaxSurgeonCapacity(int maxSurgeonCapacity)
{
	_maxSurgeonCapacity = maxSurgeonCapacity;
}

void SurgeonsTime::setActualWorkingTime(int actualWorkingTime)
{
	_actualWorkingTime = actualWorkingTime;
}

int SurgeonsTime::maxSurgeonCapacity() const
{
	return _maxSurgeonCapacity;
}

int SurgeonsTime::actualWorkingTime() const
{
	return _actualWorkingTime;
}
