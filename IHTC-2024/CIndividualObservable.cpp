#include "CIndividualObservable.h"

CIndividualObservable::CIndividualObservable(ICObservable<SolutionData>& observable, const ProblemData& problemData) :
	_observable(observable),
	_problemData(problemData)
{
}

void CIndividualObservable::consume(const CIndividual& current, const CIndividual& best, double temperature)
{
	_observable.notify(SolutionData(_problemData, current));
	// todo: best support
}
