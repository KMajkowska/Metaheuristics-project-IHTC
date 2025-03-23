#include "BestOfN.h"

BestOfN::BestOfN(int N) : _N(N)
{
	if (N <= 0 || N % 2 == 0)
	{
		throw std::invalid_argument("N must be a positive, odd number");
	}
}

Winner BestOfN::checkWinner(const CPlayer& local, const CPlayer& opponent)
{
	int requiredWins = (_N / 2) + 1;

	if (local.score() >= requiredWins)
	{
		return Winner::LOCAL;
	}

	if (opponent.score() >= requiredWins)
	{
		return Winner::OPPONENT;
	}

	return Winner::NOT_FINISHED;
}
