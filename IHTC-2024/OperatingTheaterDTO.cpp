#include "OperatingTheaterDTO.h"

std::string OperatingTheaterDTO::getId() const
{
    return id;
}

std::vector<int> OperatingTheaterDTO::getAvailability()
{
    return availability;
}
