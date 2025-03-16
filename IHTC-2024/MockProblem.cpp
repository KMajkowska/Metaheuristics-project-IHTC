#include "MockProblem.h"

MockProblem::MockProblem(double evalReturn) :
	_evalReturn(evalReturn)
{}

std::pair<double, ViolatedRestrictions> MockProblem::eval(const CIndividual & individual) const
{
	return std::make_pair(_evalReturn, ViolatedRestrictions());
}
