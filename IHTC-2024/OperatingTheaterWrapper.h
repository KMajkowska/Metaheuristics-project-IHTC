#pragma once

#include <compare>

#include "OperatingTheaterInfo.h"

struct OperatingTheaterWrapper
{
	OperatingTheaterWrapper(OperatingTheaterInfo&& ot);

	OperatingTheaterInfo& operatingTheater;

	std::strong_ordering operator<=>(const OperatingTheaterWrapper&) const;
};