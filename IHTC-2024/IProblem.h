#pragma once

#include "ISelector.h"
#include "ViolatedRestrictions.h"

class IProblem
{
public:
	virtual std::pair<double, ViolatedRestrictions> eval(const CIndividual& individual) const = 0;
};