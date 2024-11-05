#pragma once

#include "OperatingTheaterInfo.h"

struct OperatingTheaterWrapper
{
	OperatingTheaterWrapper(const OperatingTheaterInfo& ot);

	OperatingTheaterInfo& operatingTheater;

	int operator<=>(const OperatingTheaterWrapper&) const;
};