#include "StopCriteriumTemperature.h"

StopCriteriumTemperature::StopCriteriumTemperature(double stopTemp) :
	IStopCriterium(),
	stopTemp(stopTemp)
{}

bool StopCriteriumTemperature::isStop(double currTemp, int iteration) const
{
	return currTemp < stopTemp;
}
