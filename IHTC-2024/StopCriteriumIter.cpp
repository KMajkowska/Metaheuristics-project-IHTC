#include "StopCriteriumIter.h"

StopCriteriumIter::StopCriteriumIter(int stopIter) :
	IStopCriterium(),
	_stopIter(stopIter)
{}

bool StopCriteriumIter::isStop(double currTemp, int iteration) const
{
	return iteration >= _stopIter;
}
