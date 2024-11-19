#pragma once

#include "ICoolingScheme.h"
#include <corecrt_math.h>

class VariableCoolingScheme : public ICoolingScheme
{
public:
	VariableCoolingScheme(int maxIter);

	double getNewTemp(double startingTemp, double currTemp, int iteration) const;

private:

	double variableCoolingFactorCoolingScheme(double startingTemp, double currTemp, int iteration, double maxIterationNumber) const;

	int maxIter;
};