#pragma once

#include "ViolatedRestrictions.h"
#include "WeightsDTO.h"
#include "solutionUtils.h"

class FitnessCalculator
{
public:
	FitnessCalculator(double multiplier);

	double calculateFitnessWithWeight(const WeightsDTO& weights, const ViolatedRestrictions& restrictions) const;

private:
	double _multiplier;
};