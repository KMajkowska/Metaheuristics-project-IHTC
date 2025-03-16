#include "VariableCoolingScheme.h"

VariableCoolingScheme::VariableCoolingScheme(int maxIter) :
	ICoolingScheme(),
	_maxIter(maxIter)
{}

double VariableCoolingScheme::getNewTemp(double startingTemp, double currTemp, int iteration) const
{
	return variableCoolingFactorCoolingScheme(startingTemp, currTemp, iteration, _maxIter);
}

double VariableCoolingScheme::variableCoolingFactorCoolingScheme(double startingTemp, double currTemp, int iteration, double maxIterationNumber) const
{
	return currTemp * 1.0 / (1.0 + 1.0 / sqrt(iteration * (maxIterationNumber + 1) + maxIterationNumber));
}
