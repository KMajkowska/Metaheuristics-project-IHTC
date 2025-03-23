#pragma once

#include <string>

class CPlayer
{
public:
	std::string name();
	int score() const;
	bool isReady() const;

	void setName(const std::string& newName);
	void setScore(int newScore);
	void setReady(bool newReady);

	CPlayer& operator+=(int additionalScore);
private:
	std::string _name { "" };
	int _score { 0 };
	bool _isReady { false };
};