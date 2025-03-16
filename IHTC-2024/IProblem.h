#pragma once

#include "ISelector.h"
#include "ViolatedRestrictions.h"

/**
 * @brief Class used as an interface to provide polymorphism when choosing problem
*/
class IProblem
{
public:
	virtual ~IProblem() = default;
	virtual std::pair<double, ViolatedRestrictions> eval(const CIndividual& individual) const = 0;
};