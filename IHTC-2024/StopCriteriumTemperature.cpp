#include "StopCriteriumTemperature.h"

StopCriteriumTemperature::StopCriteriumTemperature(double stopTemp) :
	IStopCriterium(),
	_stopTemp(stopTemp)
{}

bool StopCriteriumTemperature::isStop(double currTemp, int iteration) const
{
	return currTemp < _stopTemp;
}
