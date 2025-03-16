#pragma once

#include "ICoolingScheme.h"

class SimplexCoolingScheme : public ICoolingScheme
{
public:
	SimplexCoolingScheme(double multiplier);

	double getNewTemp(double startingTemp, double currTemp, int iteration) const override;

private:
	double multiplier;
};