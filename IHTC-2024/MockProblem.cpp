#include "MockProblem.h"

MockProblem::MockProblem(double evalReturn) :
	evalReturn(evalReturn)
{}

double MockProblem::eval(const CIndividual & individual) const
{
	return evalReturn;
}
