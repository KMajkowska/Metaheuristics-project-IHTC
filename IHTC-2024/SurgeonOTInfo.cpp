#include "SurgeonOTInfo.h"

SurgeonOTInfo::SurgeonOTInfo(int maxOTCapacity) : _maxOTCapacity(maxOTCapacity)
{}

bool SurgeonOTInfo::isOTOvercrowded() const
{
    int actualOTWorkingTime { 0 };

    for (const auto& surgeon: _surgeonsOperations)
    {
        actualOTWorkingTime += surgeon.second.actualWorkingTime();
    }

    return actualOTWorkingTime > _maxOTCapacity;
}

void SurgeonOTInfo::setMaxOTCapacity(int maxOTCapacity)
{
    _maxOTCapacity = maxOTCapacity;
}

void SurgeonOTInfo::setSurgeonsOperations(std::map<std::string, SurgeonsTime>&& surgeonOperations)
{
    _surgeonsOperations = std::move(surgeonOperations);
}

int SurgeonOTInfo::maxOTCapacity() const
{
    return _maxOTCapacity;
}

std::map<std::string, SurgeonsTime>& SurgeonOTInfo::surgeonsOperations()
{
    return _surgeonsOperations;
}
