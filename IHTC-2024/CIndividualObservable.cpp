#include "CIndividualObservable.h"

CIndividualObservable::CIndividualObservable(const ProblemData& problemData) :
	_problemData(problemData)
{
}

void CIndividualObservable::consume(const CIndividual& current, const CIndividual& best, double temperature)
{
	notify(SolutionData(_problemData, current));
	// todo: best support
}
