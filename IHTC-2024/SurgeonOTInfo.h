#pragma once
#include <map>
#include <string>
#include "SurgeonsTime.h"

class SurgeonOTInfo
{
public:
	SurgeonOTInfo(int maxOTCapacity);
	SurgeonOTInfo() = default;

	bool isOTOvercrowded() const;

	void setMaxOTCapacity(int maxOTCapacity);
	void setSurgeonsOperations(std::map<std::string, SurgeonsTime>&& surgeonOperations);

	int maxOTCapacity() const;
	std::map<std::string, SurgeonsTime>& surgeonsOperations();

private:
	int _maxOTCapacity;
	std::map<std::string, SurgeonsTime> _surgeonsOperations;
};
