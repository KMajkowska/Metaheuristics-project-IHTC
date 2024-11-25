#pragma once
#include "WeightsDTO.h"
#include "ViolatedRestrictions.h"

static double calculateWeights(double hRestrictionModifier, const WeightsDTO& weights, const ViolatedRestrictions& restrictions);

static double calculateNewTemp(double currTemp, int iteration);
