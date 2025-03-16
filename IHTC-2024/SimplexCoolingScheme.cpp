#include "SimplexCoolingScheme.h"

SimplexCoolingScheme::SimplexCoolingScheme(double multiplier) :
	ICoolingScheme(),
	_multiplier(multiplier)
{}

double SimplexCoolingScheme::getNewTemp(double startingTemp, double currTemp, int iteration) const
{
	return _multiplier * currTemp;
}
