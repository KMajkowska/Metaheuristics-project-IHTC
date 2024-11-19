#include "FitnessCalculator.h"

FitnessCalculator::FitnessCalculator(int multiplier) :
	multiplier(multiplier)
{}

double FitnessCalculator::calculateFitnessWithWeight(const WeightsDTO& weights, const ViolatedRestrictions& restrictions) const
{
	return calculateFitness(multiplier, weights, restrictions);
}
