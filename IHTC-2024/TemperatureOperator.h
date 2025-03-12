#pragma once

#include <cfloat>
#include "ViolatedRestrictions.h"

#include "ICoolingScheme.h"

/**
 * @brief 
*/
class TemperatureOperator
{
public:
	TemperatureOperator(const ICoolingScheme& coolingScheme, int iterationWithoutChange);

	double getNewTemp(double startingTemp, double currTemp, int iteration, ViolatedRestrictions currRestr);

private:
	int iterationWithoutChange;

	int currIterationWithoutChange { 0 };
	int currRestrainFromCooling { 0 };

	ViolatedRestrictions prevRestr;

	const ICoolingScheme& coolingScheme;	
};