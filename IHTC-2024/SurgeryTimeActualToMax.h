#pragma once

#include <vector>
#include "SurgeonDTO.h"
#include "OperatingTheaterDTO.h"

struct SurgeryTimeActualToMax
{
	SurgeryTimeActualToMax() = default;
	SurgeryTimeActualToMax(const std::vector<int>& max);
	SurgeryTimeActualToMax(const SurgeonDTO& surgeon);
	SurgeryTimeActualToMax(const OperatingTheaterDTO& ot);

	std::vector<int> max;
	std::vector<int> current;
};