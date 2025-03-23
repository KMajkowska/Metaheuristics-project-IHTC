#pragma once

#include <memory>
#include <stdexcept>

#include "IWinnerJudge.h"

class BestOfN : public IWinnerJudge
{
public:
	BestOfN(int N);
	~BestOfN() {};

	Winner checkWinner(const CPlayer& local, const CPlayer& opponent) override;

private:
	int _N { 1 };
};