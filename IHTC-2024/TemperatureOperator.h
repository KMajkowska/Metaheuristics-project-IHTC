#pragma once

#include <cfloat>
#include "ViolatedRestrictions.h"

#include "ICoolingScheme.h"

/**
 * @brief Calculate new temperature based on the given CoolingSchema and criterium if ay hard restriction change
*/
class TemperatureOperator
{
public:
	TemperatureOperator(const ICoolingScheme& coolingScheme, int iterationWithoutChange);

	/**
	 * @brief Calculate new temperature for SA algorithm
	 * @param startingTemp starting temp of SA
	 * @param currTemp actual temp of SQA
	 * @param iteration which iteration is right now calculated
	 * @param currRestr which restrictions are broken
	 * @return new temperature for SA
	*/
	double getNewTemp(double startingTemp, double currTemp, int iteration, ViolatedRestrictions currRestr);

private:
	int _iterationWithoutChange;

	int _currIterationWithoutChange { 0 };
	int _currRestrainFromCooling { 0 };

	ViolatedRestrictions _prevRestr;

	const ICoolingScheme& _coolingScheme;	
};