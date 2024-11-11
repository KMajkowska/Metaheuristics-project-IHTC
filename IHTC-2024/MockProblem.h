#pragma once

#include "IProblem.h"

class MockProblem : public IProblem
{
public:
	MockProblem(double evalReturn);

	std::pair<double, ViolatedRestrictions> eval(const CIndividual& individual) const;

private:
	double evalReturn;
};