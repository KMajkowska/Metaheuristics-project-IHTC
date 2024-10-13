#pragma once

#include "IProblem.h"

class MockProblem : public IProblem
{
public:
	MockProblem(double evalReturn);

	double eval(const CIndividual& individual) const;

private:
	double evalReturn;
};