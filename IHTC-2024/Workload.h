#pragma once

#include <vector>

#include "SurgeonDTO.h"
#include "OperatingTheaterDTO.h"
#include "NurseDTO.h"


/**
 * @brief Class to represent info about actual and max nurse workload on given day and shift
*/
class Workload
{
public:
	Workload() = default;
	Workload(const std::vector<int>& max);
	Workload(const SurgeonDTO& surgeon);
	Workload(const OperatingTheaterDTO& ot);
	Workload(const NurseDTO& nurse, int days, const std::unordered_map<std::string, int> shiftNameToPos);

	void setMax(std::vector<int>&& max);
	void setCurrent(std::vector<int>&& current);

	std::vector<int>& max();
	std::vector<int>& current();

private:
	std::vector<int> _max;
	std::vector<int> _current;
};