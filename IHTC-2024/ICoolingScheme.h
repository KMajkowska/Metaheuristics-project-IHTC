#pragma once

/**
 * @brief Class used as an interface to have polymorphism when using different ways of cooling SA algorithm
*/
class ICoolingScheme
{
public:
	ICoolingScheme() = default;

	virtual double getNewTemp(double startingTemp, double currTemp, int iteration) const = 0;
};