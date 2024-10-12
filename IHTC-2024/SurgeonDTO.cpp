#include "SurgeonDTO.h"

std::string SurgeonDTO::getId() const
{
    return id;
}

std::vector<int> SurgeonDTO::getMaxSurgeryTime()
{
    return max_surgery_time;
}
