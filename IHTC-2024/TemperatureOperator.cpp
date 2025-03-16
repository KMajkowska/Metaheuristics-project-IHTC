#include "TemperatureOperator.h"

TemperatureOperator::TemperatureOperator(const ICoolingScheme& coolingScheme, int iterationWithoutChange) :
	_coolingScheme(coolingScheme),
	_iterationWithoutChange(iterationWithoutChange)
{}

double TemperatureOperator::getNewTemp(double startingTemp, double currTemp, int iteration, ViolatedRestrictions currRestr)
{
	int currTotal = currRestr.countTotalHard();

	if (currTotal > 0)
	{
		if ((--_currRestrainFromCooling) > 0)
		{
			return currTemp;
		}

		if (_prevRestr.countTotalHard() == currTotal)
		{
			if ((++_currIterationWithoutChange) >= _iterationWithoutChange)
			{
				_currRestrainFromCooling = _iterationWithoutChange;
				_currIterationWithoutChange = 0;
			}
		}

		_prevRestr = currRestr;
	}
	

	return _coolingScheme.getNewTemp(startingTemp, currTemp, iteration);
}
