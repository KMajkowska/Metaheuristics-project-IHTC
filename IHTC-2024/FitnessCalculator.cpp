#include "FitnessCalculator.h"

FitnessCalculator::FitnessCalculator(double multiplier) :
	_multiplier(multiplier)
{}

double FitnessCalculator::calculateFitnessWithWeight(const WeightsDTO& weights, const ViolatedRestrictions& restrictions) const
{
	return calculateFitness(_multiplier, weights, restrictions);
}
