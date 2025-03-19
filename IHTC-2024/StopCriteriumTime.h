#pragma once

#include <chrono>

#include "IStopCriterium.h"

/**
 * @brief Stop criterion based on the number of iterations.
 */
class StopCriteriumTime : public IStopCriterium
{
public:
    /**
     * @brief Constructor to set the iteration limit.
     * @param millis
     */
    StopCriteriumTime(int millis);

    bool isStop(double currTemp, int iteration) const override;

private:
    int _millis; /// Time after which to stop.
    std::chrono::steady_clock::time_point _startTime; /// Time of start

};
