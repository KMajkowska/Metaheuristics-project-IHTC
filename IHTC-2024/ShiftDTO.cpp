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
