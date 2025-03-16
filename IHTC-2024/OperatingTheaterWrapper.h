#pragma once

#include <compare>

#include "OperatingTheaterInfo.h"

/**
 * @brief Wrapper for operating theater class to allow us to compare two operating theaters and use this to choose
 *  which nurse is better to assign when we modify our solution
*/
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