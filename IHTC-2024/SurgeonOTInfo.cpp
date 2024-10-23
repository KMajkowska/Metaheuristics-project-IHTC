#include "SurgeonOTInfo.h"

SurgeonOTInfo::SurgeonOTInfo(int maxOTCapacity) : maxOTCapacity(maxOTCapacity)
{}

bool SurgeonOTInfo::isOTOvercrowded() const
{
    int actualOTWorkingTime = 0;
    for (const auto& surgeon: surgeonsOperations)
    {
        actualOTWorkingTime += surgeon.second.actualWorkingTime;
    }

    return actualOTWorkingTime > maxOTCapacity;
}
