#pragma once

#include <compare>

#include "OperatingTheaterInfo.h"

class OperatingTheaterWrapper
{
public:
	OperatingTheaterWrapper(const OperatingTheaterInfo& ot);

	void setOperatingTheater(OperatingTheaterInfo&& operatingTheater);

	OperatingTheaterInfo& operatingTheater();
	const OperatingTheaterInfo& operatingTheater() const;

	std::strong_ordering operator<=>(const OperatingTheaterWrapper&) const;
private:
	OperatingTheaterInfo _operatingTheater;
};