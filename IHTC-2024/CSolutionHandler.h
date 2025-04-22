#pragma once
#include <vector>
#include "SolutionData.h"

class CSolutionHandler
{
public:
	~CSolutionHandler() = default;

	void setCurrentLocal(SolutionData solution);
	void setCurrentOpponent(SolutionData solution);
	void setBestLocal(SolutionData solution);
	void setBestOpponent(SolutionData solution);

	SolutionData& currentLocal();
	SolutionData& currentOpponent();
	SolutionData& bestLocal();
	SolutionData& bestOpponent();

	virtual void consumeLocal(SolutionData solution);
	virtual void consumeOpponent(SolutionData solution);

protected:
	SolutionData _currentLocal;
	SolutionData _currentOpponent;

	SolutionData _bestLocal;
	SolutionData _bestOpponent;
};