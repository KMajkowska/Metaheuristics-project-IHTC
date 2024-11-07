#include "OperatingTheaterWrapper.h"

OperatingTheaterWrapper::OperatingTheaterWrapper(OperatingTheaterInfo&& ot) :
	operatingTheater(ot)
{
}

int OperatingTheaterWrapper::operator<=>(const OperatingTheaterWrapper& other) const
{
	if (operatingTheater.max != other.operatingTheater.max)
	{
		return operatingTheater.max > other.operatingTheater.max ? 1 : -1;
	}

	return 0;
}
