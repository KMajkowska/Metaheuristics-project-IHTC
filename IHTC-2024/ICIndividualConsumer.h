#pragma once

#include "CIndividual.h"

class ICIndividualConsumer
{
public:
	virtual ~ICIndividualConsumer() = default;

	virtual void consume(const CIndividual& current, const CIndividual& best, double temperature) = 0;

};