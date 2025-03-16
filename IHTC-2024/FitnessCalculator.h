#pragma once

#include "ViolatedRestrictions.h"
#include "WeightsDTO.h"
#include "solutionUtils.h"

/**
 * @brief Calculating how good is our solution
*/
class FitnessCalculator
{
public:
	FitnessCalculator(double multiplier);

	double calculateFitnessWithWeight(const WeightsDTO& weights, const ViolatedRestrictions& restrictions) const;

private:
	double _multiplier;
};