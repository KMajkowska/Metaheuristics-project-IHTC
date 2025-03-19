#pragma once

#include "ICIndividualConsumer.h"
#include "ICObservable.h"
#include "SolutionData.h"

/**
 * @brief Allows notification of observable with data consumed from algorithm
 */
class CIndividualObservable : public ICIndividualConsumer
{
public:
	CIndividualObservable(ICObservable<SolutionData>& observable, const ProblemData& problemData);

	void consume(const CIndividual& current, const CIndividual& best, double temperature);

private:
	ICObservable<SolutionData>& _observable;
	const ProblemData& _problemData;
};