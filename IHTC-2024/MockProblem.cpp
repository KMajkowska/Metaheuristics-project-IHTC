#include "MockProblem.h"

MockProblem::MockProblem(double evalReturn) :
	evalReturn(evalReturn)
{}

std::pair<double, ViolatedRestrictions> MockProblem::eval(const CIndividual & individual) const
{
	return std::make_pair(evalReturn, ViolatedRestrictions());
}
