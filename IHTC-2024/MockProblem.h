#pragma once

#include "IProblem.h"

/**
 * @brief Mocking problem to check if algorithm works correctly by mocking data
*/
class MockProblem : public IProblem
{
public:
	MockProblem(double evalReturn);

	std::pair<double, ViolatedRestrictions> eval(const CIndividual& individual) const override;

private:
	double _evalReturn;
};