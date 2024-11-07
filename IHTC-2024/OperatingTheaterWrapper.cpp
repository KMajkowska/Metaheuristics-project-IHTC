#include "OperatingTheaterWrapper.h"

OperatingTheaterWrapper::OperatingTheaterWrapper(OperatingTheaterInfo&& ot) :
	operatingTheater(ot)
{}

std::strong_ordering OperatingTheaterWrapper::operator<=>(const OperatingTheaterWrapper& other) const
{
	return operatingTheater.max <=> other.operatingTheater.max;
}

