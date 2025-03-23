#pragma once

#include <memory>

#include "CPlayer.h"
#include "Winner.h"

class IWinnerJudge
{
public:
	// virtual ~IWinnerJudge() = 0;

	virtual Winner checkWinner(const CPlayer& local, const CPlayer& opponent) = 0;
};