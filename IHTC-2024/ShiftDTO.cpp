#include "ShiftDTO.h"

int ShiftDTO::getDay() const
{
    return day;
}

std::string ShiftDTO::getShift() const
{
    return shift;
}

int ShiftDTO::getMaxLoad() const
{
    return max_load;
}

void ShiftDTO::setDay(int newDay)
{
    day = newDay;
}

void ShiftDTO::setShift(std::string newShift)
{
    shift = newShift;
}

void ShiftDTO::setMaxLoad(int newMaxLoad)
{
    max_load = newMaxLoad;
}