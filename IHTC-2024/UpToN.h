#pragma once


#include <memory>
#include <stdexcept>

#include "IWinnerJudge.h"
/**
 * @brief Class which represents one of the winnig solution
*/
class UpToN : public IWinnerJudge
{
public:
	UpToN(int N);
	~UpToN() {};

	Winner checkWinner(const CPlayer& local, const CPlayer& opponent) override;

private:
	int _N{ 1 };
};