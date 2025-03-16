#pragma once

#include "ICoolingScheme.h"

/**
 * @brief SImple cooling schema which is multiplying our current temperature by multiplier smaller than 1
*/
class SimplexCoolingScheme : public ICoolingScheme
{
public:
	SimplexCoolingScheme(double multiplier);

	double getNewTemp(double startingTemp, double currTemp, int iteration) const override;

private:
	double _multiplier;
};