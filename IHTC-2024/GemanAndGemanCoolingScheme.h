#pragma once

#include <corecrt_math.h>

#include "ICoolingScheme.h"

class GemanAndGemanCoolingScheme : public ICoolingScheme
{
public:
	double getNewTemp(double startingTemp, double currTemp, int iteration) const;
};