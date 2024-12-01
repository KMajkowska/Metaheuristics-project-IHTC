#include "TemperatureOperator.h"

TemperatureOperator::TemperatureOperator(const ICoolingScheme& coolingScheme, int iterationWithoutChange) :
	coolingScheme(coolingScheme),
	iterationWithoutChange(iterationWithoutChange)
{}

double TemperatureOperator::getNewTemp(double startingTemp, double currTemp, int iteration, ViolatedRestrictions currRestr)
{
	int currTotal = currRestr.countTotalHard();

	if (currTotal > 0)
	{
		if ((--currRestrainFromCooling) > 0)
		{
			return currTemp;
		}

		if (prevRestr.countTotalHard() == currTotal)
		{
			if ((++currIterationWithoutChange) >= iterationWithoutChange)
			{
				currRestrainFromCooling = iterationWithoutChange;
				currIterationWithoutChange = 0;
			}
		}

		prevRestr = currRestr;
	}
	

	return coolingScheme.getNewTemp(startingTemp, currTemp, iteration);
}
