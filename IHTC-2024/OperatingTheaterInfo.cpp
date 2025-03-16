#include "OperatingTheaterInfo.h"

OperatingTheaterInfo::OperatingTheaterInfo(int max, int current, const std::string& id) :
	_max(max),
	_current(current),
	_id(id)
{}

void OperatingTheaterInfo::setMax(int max)
{
	_max = max;
}

void OperatingTheaterInfo::setCurrent(int current)
{
	_current = current;
}

void OperatingTheaterInfo::setId(const std::string& id)
{
	_id = id;
}

int OperatingTheaterInfo::max() const
{
	return _max;
}

int OperatingTheaterInfo::current() const
{
	return _current;
}

std::string OperatingTheaterInfo::id() const
{
	return _id;
}
