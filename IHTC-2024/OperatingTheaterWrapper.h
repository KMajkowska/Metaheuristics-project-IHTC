#pragma once

#include <compare>

#include "OperatingTheaterInfo.h"

struct OperatingTheaterWrapper
{
	OperatingTheaterWrapper(const OperatingTheaterInfo& ot);

	OperatingTheaterInfo operatingTheater;

	std::strong_ordering operator<=>(const OperatingTheaterWrapper&) const;
};