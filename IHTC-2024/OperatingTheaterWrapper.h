#pragma once

#include <compare>

#include "OperatingTheaterInfo.h"

/**
 * @brief Wrapper for operating theater class to allow us to compare two operating theaters and use this to choose
 *  which nurse is better to assign when we modify our solution
*/
struct OperatingTheaterWrapper
{
	OperatingTheaterWrapper(const OperatingTheaterInfo& ot);

	OperatingTheaterInfo operatingTheater;

	std::strong_ordering operator<=>(const OperatingTheaterWrapper&) const;
};