#pragma once

#include "CIndividual.h"

/**
 * @brief Interface between whatever and solver. For example loggers.
*/
class ICIndividualConsumer
{
public:
	virtual ~ICIndividualConsumer() = default;

	virtual void consume(const CIndividual& current, const CIndividual& best, double temperature) = 0;

};