#include "GemanAndGemanCoolingScheme.h"

double GemanAndGemanCoolingScheme::getNewTemp(double startingTemp, double currTemp, int iteration) const
{
	return startingTemp / log(1 + iteration);
}
