#pragma once

#include "ICIndividualConsumer.h"
#include "CObservable.h"
#include "SolutionData.h"

/**
 * @brief Allows notification of observable with data consumed from algorithm
 */
class CIndividualObservable : public ICIndividualConsumer, public CObservable<SolutionData>
{
public:
	CIndividualObservable(const ProblemData& problemData);

	void consume(const CIndividual& current, const CIndividual& best, double temperature);

private:
	const ProblemData& _problemData;
};