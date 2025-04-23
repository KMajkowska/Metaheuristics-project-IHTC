#pragma once

#include <memory>
#include <stdexcept>

#include "IWinnerJudge.h"

/**
 * @brief Class which represents one of the winnig solution
*/
class BestOfN : public IWinnerJudge
{
public:
	BestOfN(int N);
	~BestOfN() {};

	Winner checkWinner(const CPlayer& local, const CPlayer& opponent) override;

private:
	int _N { 1 };
};