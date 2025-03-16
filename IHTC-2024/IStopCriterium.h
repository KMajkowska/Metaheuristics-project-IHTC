#pragma once

/**
 * @brief Interface for stop criteria.
 *
 * We use this class as an interface, as we can have multiple stop criteria and we want to make this polymorphic.
 */
class IStopCriterium
{
public:
    IStopCriterium() = default;
	virtual ~IStopCriterium() = default;

    /**
     * @brief Check if the stop criterion is met.
     *
     * @param currTemp Current temperature of the algorithm.
     * @param iteration Current iteration number.
     * @return `true` if the criterion is met, otherwise `false`.
     */
	virtual bool isStop(double currTemp, int iteration) const = 0;
};
