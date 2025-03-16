#pragma once

#include <corecrt_math.h>

#include "ICoolingScheme.h"

/**
 * @brief Cooling schema described by Stuart Geman and Donald Geman
 * https://www.fys.ku.dk/~andresen/BAhome/ownpapers/perm-annealSched.pdf
*/
class GemanAndGemanCoolingScheme : public ICoolingScheme
{
public:
	double getNewTemp(double startingTemp, double currTemp, int iteration) const override;
};