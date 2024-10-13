#pragma once

#include "ISelector.h"

class IProblem
{
public:
	virtual double eval(const CIndividual& individual) const = 0;
};