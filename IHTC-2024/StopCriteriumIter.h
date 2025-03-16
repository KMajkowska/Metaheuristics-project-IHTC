#pragma once

#include "IStopCriterium.h"

/**
 * @brief Stop criterion based on the number of iterations.
 */
class StopCriteriumIter : public IStopCriterium
{
public:
    /**
     * @brief Constructor to set the iteration limit.
     * @param stopIter Maximum number of iterations before stopping.
     */
    StopCriteriumIter(int stopIter);

	bool isStop(double currTemp, int iteration) const override;

private:
    int _stopIter; ///< Maximum allowed iterations.
};
