#pragma once

class ICoolingScheme
{
public:
	~ICoolingScheme() = default;

	virtual double getNewTemp(double startingTemp, double currTemp, int iteration) const = 0;
};