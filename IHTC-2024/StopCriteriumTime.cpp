#include "StopCriteriumTime.h"

StopCriteriumTime::StopCriteriumTime(int millis) :
	_millis(millis),
	_startTime(std::chrono::steady_clock::now())
{}

bool StopCriteriumTime::isStop(double currTemp, int iteration) const
{
	auto now = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime).count() >= _millis;
}
