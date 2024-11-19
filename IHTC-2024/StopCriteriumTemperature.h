#pragma once

#include "IStopCriterium.h"

class StopCriteriumTemperature : public IStopCriterium
{
public:
	StopCriteriumTemperature(double stopTemp);

	bool isStop(double currTemp, int iteration) const;

private:
	double stopTemp;
};