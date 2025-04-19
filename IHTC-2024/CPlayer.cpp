#include "CPlayer.h"

CPlayer::CPlayer(const std::string& name) : _name(name)
{}

std::string CPlayer::name()
{
    return _name;
}

int CPlayer::score() const
{
    return _score;
}

bool CPlayer::isReady() const
{
    return _isReady;
}

void CPlayer::setName(const std::string& newName)
{
    _name = newName;
}

void CPlayer::setScore(int newScore)
{
    _score = newScore;
}

void CPlayer::setReady(bool newReady)
{
    _isReady = newReady;
}

CPlayer& CPlayer::operator+=(int additionalScore)
{
    _score += additionalScore;

    return *this;
}
