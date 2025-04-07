#pragma once

#include "ICoolingScheme.h"
#include <corecrt_math.h>


/**
 * @brief Cooling schema which calculate new temperature based on mathematical equation currTemp * 1.0 / (1.0 + 1.0 / sqrt(iteration * (maxIterationNumber + 1) + maxIterationNumber))
*/
class VariableCoolingScheme : public ICoolingScheme
{
public:
	VariableCoolingScheme(int maxIter);

	double getNewTemp(double startingTemp, double currTemp, int iteration) const override;

private:

	int _maxIter;
};