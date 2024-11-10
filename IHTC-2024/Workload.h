#pragma once

#include <vector>

#include "SurgeonDTO.h"
#include "OperatingTheaterDTO.h"
#include "NurseDTO.h"

struct Workload
{
	Workload() = default;
	Workload(const std::vector<int>& max);
	Workload(const SurgeonDTO& surgeon);
	Workload(const OperatingTheaterDTO& ot);
	Workload(const NurseDTO& nurse, int days, const std::unordered_map<std::string, int> shiftNameToPos);

	std::vector<int> max;
	std::vector<int> current;
};