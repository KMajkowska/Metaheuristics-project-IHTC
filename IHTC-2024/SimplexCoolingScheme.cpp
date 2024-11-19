#include "SimplexCoolingScheme.h"

SimplexCoolingScheme::SimplexCoolingScheme(double multiplier) :
	ICoolingScheme(),
	multiplier(multiplier)
{}

double SimplexCoolingScheme::getNewTemp(double startingTemp, double currTemp, int iteration) const
{
	return multiplier * currTemp;
}
