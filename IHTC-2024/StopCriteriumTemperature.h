#pragma once

#include "IStopCriterium.h"

/**
 * @brief Stop criterion based on the number of temperature.
 */
class StopCriteriumTemperature : public IStopCriterium
{
public:
	/**
	* @brief Constructor to set the temperature limit.
	* @param stopTemp Minimum temperature before stopping.
	*/
	StopCriteriumTemperature(double stopTemp);

	bool isStop(double currTemp, int iteration) const override;

private:
	double stopTemp;
};