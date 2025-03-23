#pragma once

#include <chrono>

#include "IStopCriterium.h"

/**
 * @brief Stop criterion based on the run time.
 */
class StopCriteriumTime : public IStopCriterium
{
public:
    /**
     * @brief Constructor to set the millis limit.
     * @param millis
     */
    StopCriteriumTime(int millis);

    bool isStop(double currTemp, int iteration) const override;

private:
    int _millis; /// Time after which to stop.
    mutable std::chrono::steady_clock::time_point _startTime { std::chrono::steady_clock::now() }; /// Time of start
    mutable bool _started { false }; /// The clock starts counting down after first 'isStop'.
};
