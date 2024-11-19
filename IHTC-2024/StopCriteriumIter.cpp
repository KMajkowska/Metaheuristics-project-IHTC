#include "StopCriteriumIter.h"

StopCriteriumIter::StopCriteriumIter(int stopIter) :
	IStopCriterium(),
	stopIter(stopIter)
{}

bool StopCriteriumIter::isStop(double currTemp, int iteration) const
{
	return iteration >= stopIter;
}
