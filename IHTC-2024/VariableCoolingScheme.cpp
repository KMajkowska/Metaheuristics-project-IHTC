#include "VariableCoolingScheme.h"

VariableCoolingScheme::VariableCoolingScheme(int maxIter) :
	ICoolingScheme(),
	_maxIter(maxIter)
{}

double VariableCoolingScheme::getNewTemp(double startingTemp, double currTemp, int iteration) const
{
	return currTemp * 1.0 / (1.0 + 1.0 / sqrt(iteration * (_maxIter + 1) + _maxIter));
}
