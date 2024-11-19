#pragma once

#include "IStopCriterium.h"

class StopCriteriumIter : public IStopCriterium
{
public:
	StopCriteriumIter(int stopIter);

	bool isStop(double currTemp, int iteration) const;

private:
	int stopIter;
};