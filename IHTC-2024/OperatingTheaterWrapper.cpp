#include "OperatingTheaterWrapper.h"

OperatingTheaterWrapper::OperatingTheaterWrapper(const OperatingTheaterInfo& ot) :
	_operatingTheater(ot)
{}

void OperatingTheaterWrapper::setOperatingTheater(OperatingTheaterInfo&& operatingTheater)
{
	_operatingTheater = std::move(operatingTheater);
}

OperatingTheaterInfo& OperatingTheaterWrapper::operatingTheater()
{
	return _operatingTheater;
}

const OperatingTheaterInfo& OperatingTheaterWrapper::operatingTheater() const
{
	return _operatingTheater;
}


std::strong_ordering OperatingTheaterWrapper::operator<=>(const OperatingTheaterWrapper& other) const
{
	return _operatingTheater.max() <=> other._operatingTheater.max();
}

