#pragma once

#include "OperatingTheaterInfo.h"

struct OperatingTheaterWrapper
{
	OperatingTheaterWrapper(OperatingTheaterInfo&& ot);

	OperatingTheaterInfo& operatingTheater;

	int operator<=>(const OperatingTheaterWrapper&) const;
};