#include "UpToN.h"

UpToN::UpToN(int N) : _N(N)
{
	if (N <= 0 )
	{
		throw std::invalid_argument("N must be a positive");
	}
}

Winner UpToN::checkWinner(const CPlayer& local, const CPlayer& opponent)
{
	if (local.score() == _N)
	{
		return Winner::LOCAL;
	}

	if (opponent.score() >= _N)
	{
		return Winner::OPPONENT;
	}

	return Winner::NOT_FINISHED;
}
